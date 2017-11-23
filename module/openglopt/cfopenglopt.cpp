#include "cfopenglopt.h"
#include "../../common/funcargs/cfargs.h"
#include "../modulemanagement/cfmm.h"
#include <QGLContext>

static const char *vertexShaderSourceCore =
    "#version 410\n"
    "layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex> \n"
    "out vec2 TexCoords;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "	gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
    "	TexCoords = vertex.zw;\n"
    "}\n";

static const char *fragmentShaderSourceCore =
    "#version 410\n"
    "in vec2 TexCoords;\n"
    "out vec4 color;\n"
    "uniform sampler2D text;\n"
    "uniform vec3 textColor;\n"
    "void main() {\n"
    "	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
    "	color = vec4(textColor, 1.0) * sampled;\n"
    "}\n";

CFFuncResults
init_gl(const CFFuncArguments& args);
CFFuncResults
query_gl_context(const CFFuncArguments& args);
CFFuncResults
texture_from_glyph(const CFFuncArguments& args);
CFFuncResults
draw_glyph(const CFFuncArguments& args);
CFFuncResults
release_texture(const CFFuncArguments& args);

CFOpenGLOpt::CFOpenGLOpt()
    : _is_init(false) {
    funcs = {
        std::make_pair(INIT_GL, &init_gl),
        std::make_pair(QUERY_GL_CONTEXT, &query_gl_context),
        std::make_pair(RELEASE_TEXTURE, &release_texture),
        std::make_pair(LOAD_FROM_GLYPH, &texture_from_glyph),
        std::make_pair(DRAW_GLYPH, &draw_glyph)
    };

    QGLFormat qglFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
    qglFormat.setVersion(4, 2);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    qglFormat.setSampleBuffers(true);
    context = new QGLContext(qglFormat);
}

CFOpenGLOpt::~CFOpenGLOpt() {

}

bool CFOpenGLOpt::hasInit() const {
    return _is_init;
}

void CFOpenGLOpt::inited() {
    _is_init = true;
}

QGLContext* CFOpenGLOpt::systemGLContext() const {
    return context;
}

CFFuncResults
init_gl(const CFFuncArguments&) {
    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFOpenGLOpt* module = (CFOpenGLOpt*)(cfmm->queryModuleInstance(OPENGL_MODULE));

    if (!module->hasInit()) {
        qDebug() << "OpenGL Versions Supported: " << QGLFormat::openGLVersionFlags() << "\n";
        printf("version: %s\n", (char*)glGetString(GL_VERSION));

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

        glShadeModel(GL_FLAT); 	// 设置阴影平滑模式
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        module->program = new QOpenGLShaderProgram;
        module->program->addShaderFromSourceCode(
                            QOpenGLShader::Vertex, vertexShaderSourceCore);
        module->program->addShaderFromSourceCode(
                            QOpenGLShader::Fragment, fragmentShaderSourceCore);

        module->program->link();
        module->program->bind();

        glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
        glUniformMatrix4fv(glGetUniformLocation(module->program->programId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        module->inited();
    }

    return CFFuncResults();
}

CFFuncResults
query_gl_context(const CFFuncArguments&) {
    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFOpenGLOpt* module = (CFOpenGLOpt*)(cfmm->queryModuleInstance(OPENGL_MODULE));

    QGLContext* context = module->systemGLContext();
    CFFuncResults reVal;
    QVariant v;
    v.setValue(context);
    reVal.pushV("context", v);
    return reVal;
}

CFFuncResults
texture_from_glyph(const CFFuncArguments& args) {
    FT_Face face = args.getV("face").value<FT_Face>();
    char cr = args.getV("char").toChar().toLatin1();

    if (FT_Load_Char(face, (FT_ULong)cr, FT_LOAD_RENDER))
        qDebug() << "ERROR::FREETYTPE: Failed to load Glyph";

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer
    );

    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    // Now store character for later use
    Character c {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        (GLuint)(face->glyph->advance.x)
    };

    CFFuncResults result;
    QVariant v;
    v.setValue(c);
    result.pushV("character", v);
    return result;
}

CFFuncResults
draw_glyph(const CFFuncArguments& args) {
    GLuint VAO = args.getV("VAO").value<GLuint>();
    GLuint VBO = args.getV("VBO").value<GLuint>();
    Character ch = args.getV("character").value<Character>();

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFOpenGLOpt* module = (CFOpenGLOpt*)(cfmm->queryModuleInstance(OPENGL_MODULE));

    glUniform3f(glGetUniformLocation(module->program->programId(), "textColor"), 1.0, 0.0, 0.0);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    GLfloat scale = 10.0f;

    GLfloat xpos = 100.0 + ch.Bearing.x * scale;
    GLfloat ypos = 100.0 - (ch.Size.y - ch.Bearing.y) * scale;

    GLfloat w = ch.Size.x * scale;
    GLfloat h = ch.Size.y * scale;
    // Update VBO for each character
    GLfloat vertices[6][4] = {
        { xpos,     ypos + h,   0.0, 0.0 },
        { xpos,     ypos,       0.0, 1.0 },
        { xpos + w, ypos,       1.0, 1.0 },

        { xpos,     ypos + h,   0.0, 0.0 },
        { xpos + w, ypos,       1.0, 1.0 },
        { xpos + w, ypos + h,   1.0, 0.0 }
    };

    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    return CFFuncResults();
}

CFFuncResults
release_texture(const CFFuncArguments& args) {

}
