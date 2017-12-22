#include "cfopenglopt.h"
#include "../../common/funcargs/cfargs.h"
#include "../modulemanagement/cfmm.h"
#include <QGLContext>
#include <QVector>

//#include <ft2build.h>
//#include FT_FREETYPE_H

const GLfloat DEFAULT_WIDTH = 100.f;
const GLfloat DEFAULT_HEIGHT = 100.f;

static const char *vertexShaderSourceCore =
    "#version 410 \n"
    "layout (location = 0) in vec4 vertex; \n"
    "out vec2 TexCoords;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "	gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
    "	TexCoords = vertex.zw;\n"
    "}";

static const char *fragmentShaderSourceCore =
    "#version 410 \n"
    "in vec2 TexCoords;\n"
    "out vec4 color;\n"
    "uniform sampler2D text;\n"
    "uniform vec3 textColor;\n"
    "uniform vec3 bkColor;\n"
    "void main() {\n"
    "	float tmp = texture(text, TexCoords).r;\n"
    "	if (tmp > 0) {\n"
    "		vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
    "		color = vec4(textColor, 1.0) * sampled ;\n"
    "	} else { \n"
    "		color = vec4(bkColor, 1.0);\n"
    "	}\n"
    "}";

static const char *vertexBackgroundShaderSourceCore =
    "#version 410\n"
    "layout (location = 0) in vec2 vertex; \n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "	gl_Position = projection * vec4(vertex.xy, 0.1, 1.0);\n"
    "}";

static const char *fragmentBackgroundShaderSourceCore =
    "#version 410\n"
    "out vec4 color;\n"
    "uniform vec3 textColor;\n"
    "void main() {\n"
    "	color = vec4(textColor, 1.0);\n"
    "}";

CFFuncResults
init_gl(const CFFuncArguments& args);
CFFuncResults
query_gl_context(const CFFuncArguments& args);
CFFuncResults
texture_from_glyph(const CFFuncArguments& args);
CFFuncResults
draw_glyph(const CFFuncArguments& args);
CFFuncResults
fill_background(const CFFuncArguments& args);
CFFuncResults
release_texture(const CFFuncArguments& args);
CFFuncResults
draw_glyph_lst(const CFFuncArguments& args);

CFOpenGLOpt::CFOpenGLOpt()
    : _is_init(false) {

    funcs.push_back(std::make_pair(INIT_GL, &init_gl));
    funcs.push_back(std::make_pair(RELEASE_TEXTURE, &release_texture));
    funcs.push_back(std::make_pair(LOAD_FROM_GLYPH, &texture_from_glyph));
    funcs.push_back(std::make_pair(DRAW_GLYPH, &draw_glyph));
    funcs.push_back(std::make_pair(DRAW_BACKGROUND, &fill_background));
    funcs.push_back(std::make_pair(DRAW_GLYPH_LST, &draw_glyph_lst));
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

    glShadeModel(GL_FLAT); 	// 设置阴影平滑模式
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
//    glEnable(GL_CULL_FACE);

    glEnable(GL_ALPHA_TEST);

    QOpenGLShaderProgram * program_bk = new QOpenGLShaderProgram;
    program_bk->addShaderFromSourceCode(
                            QOpenGLShader::Vertex, vertexBackgroundShaderSourceCore);
    program_bk->addShaderFromSourceCode(
                            QOpenGLShader::Fragment, fragmentBackgroundShaderSourceCore);

    QOpenGLShaderProgram * program = new QOpenGLShaderProgram;
    program->addShaderFromSourceCode(
                            QOpenGLShader::Vertex, vertexShaderSourceCore);
    program->addShaderFromSourceCode(
                            QOpenGLShader::Fragment, fragmentShaderSourceCore);

    QVariant v;
    v.setValue(program);
    QVariant v_bk;
    v_bk.setValue(program_bk);
    CFFuncResults result;
    result.pushV("program", v);
    result.pushV("program_bk", v_bk);

    return result;
}

CFFuncResults
query_gl_context(const CFFuncArguments&) {
//    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
//    CFOpenGLOpt* module = (CFOpenGLOpt*)(cfmm->queryModuleInstance(OPENGL_MODULE));

//    QGLContext* context = module->systemGLContext();
//    CFFuncResults reVal;
//    QVariant v;
//    v.setValue(context);
//    reVal.pushV("context", v);
//    return reVal;
    return CFFuncResults();
}

CFFuncResults
texture_from_glyph(const CFFuncArguments& args) {
    FT_Face face = args.getV("face").value<FT_Face>();
    FT_ULong charcode = args.getV("charcode").value<FT_ULong>();
//    FT_UInt gindex = args.getV("gindex").value<FT_UInt>();

    // font 18

    FT_Set_Pixel_Sizes(face, 0, 48);
    FT_Set_Char_Size(face, 0, 18<<6, 300, 300);

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

    // Now store character for later use
    Character c;
    c.TextureID = texture;
    c.Size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
    c.Bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
    c.Advance = (GLuint)(face->glyph->advance.x);
    c.Height = (GLuint)(face->height);
//    {
//        texture,
//        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//        (GLuint)(face->glyph->advance.x)
//    };

    CFFuncResults result;
    QVariant v;
    v.setValue(c);
    result.pushV("character", v);

//    char name_buf[256];
//    memset(name_buf, sizeof(char), sizeof(name_buf));

//    if (FT_HAS_GLYPH_NAMES(face)) {
//        QVariant v;
//        if (FT_Get_Glyph_Name(face, gindex, name_buf, 256)) {
//            QString str = QString(QLatin1String(name_buf));
//            v.setValue(str);
//        }
//        result.pushV("name", v);
//    }

    return result;
}

CFFuncResults
draw_glyph(const CFFuncArguments& args) {
    GLuint VAO = args.getV("VAO").value<GLuint>();
    GLuint VBO = args.getV("VBO").value<GLuint>();
    Character ch = args.getV("character").value<Character>();
    QOpenGLShaderProgram* program = args.getV("program").value<QOpenGLShaderProgram*>();


    program->link();
    program->bind();

    glm::mat4 projection = glm::ortho(0.0f, DEFAULT_WIDTH, 0.0f, DEFAULT_HEIGHT);
    glUniformMatrix4fv(glGetUniformLocation(program->programId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform3f(glGetUniformLocation(program->programId(), "textColor"), 0.0, 0.0, 0.0);
    glUniform3f(glGetUniformLocation(program->programId(), "bkColor"), 1.0, 1.0, 1.0);
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
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    return CFFuncResults();
}


CFFuncResults
fill_background(const CFFuncArguments& args) {
    GLuint VAO = args.getV("VAO").value<GLuint>();
    GLuint VBO = args.getV("VBO").value<GLuint>();
    QOpenGLShaderProgram* program = args.getV("program").value<QOpenGLShaderProgram*>();

    QColor bkg_color = args.getV("bkg_color").value<QColor>();
    GLfloat red = bkg_color.redF();
    GLfloat green = bkg_color.greenF();
    GLfloat blue = bkg_color.blueF();

    program->link();
    program->bind();

    glm::mat4 projection = glm::ortho(0.0f, DEFAULT_WIDTH, 0.0f, DEFAULT_HEIGHT);
    glUniformMatrix4fv(glGetUniformLocation(program->programId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(program->programId(), "textColor"), red, green, blue);
    glBindVertexArray(VAO);

    GLfloat xpos = 0;
    GLfloat ypos = 0;

    GLfloat w = DEFAULT_WIDTH;
    GLfloat h = DEFAULT_HEIGHT;
    // Update VBO for each character
    GLfloat vertices[6][2] = {
        { xpos,     ypos + h },
        { xpos,     ypos },
        { xpos + w, ypos },

        { xpos,     ypos + h },
        { xpos + w, ypos },
        { xpos + w, ypos + h }
    };

    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return CFFuncResults();
}

CFFuncResults
release_texture(const CFFuncArguments& args) {

}

CFFuncResults
draw_glyph_lst(const CFFuncArguments& args) {
    GLuint VAO = args.getV("VAO").value<GLuint>();
    GLuint VBO = args.getV("VBO").value<GLuint>();
    QVector<Character> text = args.getV("char-lst").value<QVector<Character> >();
    GLfloat x = args.getV("x").value<GLfloat>();
    GLfloat y = args.getV("y").value<GLfloat>();
    GLfloat w = args.getV("w").value<GLfloat>();
    GLfloat h = args.getV("h").value<GLfloat>();
    GLfloat scale = args.getV("scale").value<GLfloat>();
    QOpenGLShaderProgram* program = args.getV("program").value<QOpenGLShaderProgram*>();

    QColor fill_color = args.getV("fill_color").value<QColor>();
    GLfloat red = fill_color.redF();
    GLfloat green = fill_color.greenF();
    GLfloat blue = fill_color.blueF();

    program->link();
    program->bind();

    glm::mat4 projection = glm::ortho(0.0f, w, 0.0f, h);
    glUniformMatrix4fv(glGetUniformLocation(program->programId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform3f(glGetUniformLocation(program->programId(), "textColor"), red, green, blue);
    glUniform3f(glGetUniformLocation(program->programId(), "bkColor"), 1.0, 1.0, 1.0);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    QVector<Character>::const_iterator c = text.begin();
    while (c != text.end()) {
        Character ch = *c;

//        GLfloat xpos = x + ch.Bearing.x * scale;
//        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
        GLfloat xpos = x;
        GLfloat ypos = y;

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
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)

        ++c;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    return CFFuncResults();
}
