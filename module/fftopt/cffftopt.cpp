#include "cffftopt.h"
#include <QString>
#include <QtOpenGL/QtOpenGL>
#include "../../common/funcargs/cfargs.h"
#include "../../module/modulemanagement/cfmm.h"

#include <QDebug>

CFFuncResults loadTTFFile(const CFFuncArguments& args);
CFFuncResults free_ttf_file(const CFFuncArguments& args);
CFFuncResults import_code_as_chars(const CFFuncArguments& args);
CFFuncResults import_code_as_symbol(const CFFuncArguments& args);

CFFftOpt::CFFftOpt() {
    funcs = {
        std::make_pair(FFT_LOAD_FILE, &loadTTFFile),
        std::make_pair(FFT_FREE_FACE, &free_ttf_file)
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

const QVector<FT_Face>& CFFftOpt::queryOpenedFaces() const {
    return faces;
}

QVector<FT_Face>& CFFftOpt::queryOpenedFaces() {
    return faces;
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

    CFFuncResults reVal;
    QVariant v(QVariant::UserType);
    v.setValue(face);
    reVal.pushV("face", v);

    opt->queryOpenedFaces().push_back(face);

    return reVal;
}

CFFuncResults
free_ttf_file(const CFFuncArguments& args) {
    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFFftOpt* opt = (CFFftOpt*)cfmm->queryModuleInstance(FFT_MODULE);
    QVector<FT_Face> faces = opt->queryOpenedFaces();
    FT_Face face = args.getV("face").value<FT_Face>();
    faces.erase(
        std::remove_if(faces.begin(), faces.end(), std::bind1st(std::equal_to<FT_Face>(), face)),
                faces.end());
    FT_Done_Face(face);

    return CFFuncResults();
}

CFFuncResults
import_code_as_chars(const CFFuncArguments& args) {

}

CFFuncResults
import_code_as_symbol(const CFFuncArguments& args) {

}


