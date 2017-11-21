#include "cffftopt.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <QString>
#include <QtOpenGL/QtOpenGL>
#include "../../common/funcargs/cfargs.h"

#include <QDebug>

CFFftOpt::CFFftOpt() {

}

CFFftOpt::~CFFftOpt() {

}

CFFuncResults
CFFftOpt::loadTTFFile(const CFFuncArguments& args) {
    const QString& path = args.getV("path").toString();

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        qDebug() << "ERROR::FREETYPE: Could not init FreeType Library";

    FT_Face face;
    int result = FT_New_Face(ft, path.toStdString().c_str(), 0, &face);
    if (result != 0) {
        qDebug() << "result :" << result;
        qDebug() << "ERROR::FREETYPE: Failed to load font";
    }

    FT_Set_Pixel_Sizes(face, 0, 60);

    if (FT_Load_Char(face, 'f', FT_LOAD_RENDER))
        qDebug() << "ERROR::FREETYTPE: Failed to load Glyph";

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

//    for (GLubyte c = 0; c < 128; c++)
//    {
//        // Load character glyph
//        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
//        {
//            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
//            continue;
//        }
//        // Generate texture
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

        // Now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (GLuint)(face->glyph->advance.x)
        };
//        Characters.insert(std::pair<GLchar, Character>(c, character));
//    }

//        this->pushChar(character);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void CFFftOpt::loadImage(const QString& path, int index) {

}

void CFFftOpt::loadStroke(const QString& path, int index) {

}
