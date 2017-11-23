#include "cffftopt.h"
#include <QString>
#include <QtOpenGL/QtOpenGL>
#include "../../common/funcargs/cfargs.h"
#include "../../module/modulemanagement/cfmm.h"

#include <QDebug>

CFFuncResults loadTTFFile(const CFFuncArguments& args);
CFFuncResults load_glyph_in_file(const CFFuncArguments& args);
CFFuncResults free_ttf_file(const CFFuncArguments& args);

CFFftOpt::CFFftOpt() {
    funcs = {
        std::make_pair(FFT_LOAD_FILE, &loadTTFFile)
    };

    if (FT_Init_FreeType(&ft))
        qDebug() << "ERROR::FREETYPE: Could not init FreeType Library";
}

CFFftOpt::~CFFftOpt() {
    FT_Done_FreeType(ft);
}

FT_Library CFFftOpt::queryFaceLib() {
    return ft;
}

void CFFftOpt::loadImage(const QString& path, int index) {

}

void CFFftOpt::loadStroke(const QString& path, int index) {

}

CFFuncResults
loadTTFFile(const CFFuncArguments& args) {

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFFftOpt* opt = (CFFftOpt*)cfmm->queryModuleInstance(FFT_MODULE);
    FT_Library ft = opt->queryFaceLib();

    const QString& path = args.getV("path").toString();
    qDebug() << "passing data : " << path;

    FT_Face face;
    int result = FT_New_Face(ft, path.toStdString().c_str(), 0, &face);
    if (result != 0) {
        qDebug() << "result :" << result;
        qDebug() << "ERROR::FREETYPE: Failed to load font";
    }

    FT_Set_Pixel_Sizes(face, 0, 60);

    if (FT_Load_Char(face, 'f', FT_LOAD_RENDER))
        qDebug() << "ERROR::FREETYTPE: Failed to load Glyph";

//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

//    GLuint texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexImage2D(
//        GL_TEXTURE_2D,
//        0,
//        GL_RED,
//        face->glyph->bitmap.width,
//        face->glyph->bitmap.rows,
//        0,
//        GL_RED,
//        GL_UNSIGNED_BYTE,
//        face->glyph->bitmap.buffer
//    );

//    // Set texture options
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    glBindTexture(GL_TEXTURE_2D, 0);

    // Now store character for later use
//    Character character {
//        texture,
//        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//        (GLuint)(face->glyph->advance.x)
//    };


    CFFuncResults reVal;
    QVariant v(QVariant::UserType);
    v.setValue(face);
    reVal.pushV("character", v);

    return reVal;
}

CFFuncResults
load_glyph_in_file(const CFFuncArguments& args) {

}

CFFuncResults
free_ttf_file(const CFFuncArguments& args) {
//    FT_Done_Face(face);
}


