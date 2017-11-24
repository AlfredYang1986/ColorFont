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

    qDebug() << "face num_faces :" << face->num_faces;
    qDebug() << "face num_glyphs :" << face->num_glyphs;
    qDebug() << "face num_charmaps :" << face->num_charmaps;
    qDebug() << "face num_fixed_sized:" << face->num_fixed_sizes;

//    FT_Set_Pixel_Sizes(face, 0, 60);

//    if (FT_Load_Char(face, 'f', FT_LOAD_RENDER))
//    if (FT_Load_Glyph(face, 0, FT_LOAD_RENDER))
//        qDebug() << "ERROR::FREETYTPE: Failed to load Glyph";

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


