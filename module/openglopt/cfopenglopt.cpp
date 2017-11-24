#include "cfopenglopt.h"
#include "../../common/funcargs/cfargs.h"
#include "../modulemanagement/cfmm.h"
#include <QGLContext>

//#include <ft2build.h>
//#include FT_FREETYPE_H

const GLfloat DEFAULT_WIDTH = 100.f;
const GLfloat DEFAULT_HEIGHT = 100.f;

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
//    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
//    CFOpenGLOpt* module = (CFOpenGLOpt*)(cfmm->queryModuleInstance(OPENGL_MODULE));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

    glShadeModel(GL_FLAT); 	// 设置阴影平滑模式
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    QOpenGLShaderProgram * program = new QOpenGLShaderProgram;
    program->addShaderFromSourceCode(
                            QOpenGLShader::Vertex, vertexShaderSourceCore);
    program->addShaderFromSourceCode(
                            QOpenGLShader::Fragment, fragmentShaderSourceCore);

    program->link();
    program->bind();

    glm::mat4 projection = glm::ortho(0.0f, DEFAULT_WIDTH, 0.0f, DEFAULT_HEIGHT);
    glUniformMatrix4fv(glGetUniformLocation(program->programId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    QVariant v;
    v.setValue(program);
    CFFuncResults result;
    result.pushV("program", v);

    return result;
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
    FT_ULong charcode = args.getV("charcode").value<FT_ULong>();

    FT_Set_Pixel_Sizes(face, 0, 60);

//    FT_Set_Char_Size(face, 0, 12<<6, 300, 300);

    if (FT_Load_Glyph(face, charcode, FT_LOAD_RENDER)) {
        qDebug() << "ERROR::FREETYTPE: Failed to load Glyph";
    }

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

    qDebug() << "test : " << texture;

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
    QOpenGLShaderProgram* program = args.getV("program").value<QOpenGLShaderProgram*>();

    glUniform3f(glGetUniformLocation(program->programId(), "textColor"), 1.0, 1.0, 1.0);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    GLfloat scale = 1.0f;
    GLfloat ad = (ch.Advance >> 6) * scale;
    GLfloat xpos = DEFAULT_WIDTH / 2 + ch.Bearing.x * scale - ad / 2;
    GLfloat ypos = DEFAULT_HEIGHT / 2 - (ch.Size.y - ch.Bearing.y) * scale - ad / 2;

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
