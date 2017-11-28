#include "cffftopt.h"
#include <QString>
#include <QtOpenGL/QtOpenGL>
#include "../../common/funcargs/cfargs.h"
#include "../../module/modulemanagement/cfmm.h"
#include <QVariant>

#include <QDebug>

CFFuncResults loadTTFFile(const CFFuncArguments& args);
CFFuncResults free_ttf_file(const CFFuncArguments& args);
CFFuncResults import_code_as_chars(const CFFuncArguments& args);
CFFuncResults import_code_as_symbol(const CFFuncArguments& args);

CFFftOpt::CFFftOpt() {
    funcs = {
        std::make_pair(FFT_LOAD_FILE, &loadTTFFile),
        std::make_pair(FFT_FREE_FACE, &free_ttf_file),
        std::make_pair(FFT_IMPORT_CHAR, &import_code_as_chars),
        std::make_pair(FFT_IMPORT_SYMBOL, &import_code_as_symbol)
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

const QVector<std::pair<QString, FT_Face> >& CFFftOpt::queryOpenedFaces() const {
    return faces;
}

QVector<std::pair<QString, FT_Face> >& CFFftOpt::queryOpenedFaces() {
    return faces;
}

CFFuncResults
loadTTFFile(const CFFuncArguments& args) {

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFFftOpt* opt = (CFFftOpt*)cfmm->queryModuleInstance(FFT_MODULE);
    FT_Library ft = opt->queryFaceLib();

    const QString& path = args.getV("path").toString();

    FT_Face face;
    int result = FT_New_Face(ft, path.toStdString().c_str(), 0, &face);
    if (result != 0) {
        qDebug() << "ERROR::FREETYPE: Failed to load font";
    }

    CFFuncResults reVal;
    QVariant v(QVariant::UserType);
    v.setValue(face);
    reVal.pushV("face", v);

    opt->queryOpenedFaces().push_back(std::make_pair(path, face));

    return reVal;
}

class path_predicate {
public:
    path_predicate(const QString& p) : _p(p) {}
    bool operator()(const std::pair<QString, FT_Face>& iter) {
        return iter.first == _p;
    }

private:
    QString _p;
};

class face_predicate {
public:
    face_predicate(FT_Face p) : _p(p) {}
    bool operator()(const std::pair<QString, FT_Face>& iter) {
        return iter.second == _p;
    }
private:
    FT_Face _p;
};

CFFuncResults
free_ttf_file(const CFFuncArguments& args) {
    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFFftOpt* opt = (CFFftOpt*)cfmm->queryModuleInstance(FFT_MODULE);
    QVector<std::pair<QString, FT_Face> > faces = opt->queryOpenedFaces();
    FT_Face face = args.getV("face").value<FT_Face>();
    faces.erase(
        std::remove_if(faces.begin(), faces.end(), face_predicate(face)),
                faces.end());
    FT_Done_Face(face);

    return CFFuncResults();
}

CFFuncResults
import_code_as_chars(const CFFuncArguments& args) {
    FT_ULong charcode = args.getV("charcode").value<FT_ULong>();
    FT_Face face = args.getV("face").value<FT_Face>();

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFFftOpt* opt = (CFFftOpt*)cfmm->queryModuleInstance(FFT_MODULE);
    QVector<std::pair<QString, FT_Face> > faces = opt->queryOpenedFaces();

    QVector<std::pair<QString, FT_Face> >::const_iterator citer =
        std::find_if(faces.begin(), faces.end(), face_predicate(face));

    QString path = (*citer).first;

    /**
     *	1. move files to certain path
     */

    QVariant vp;
    vp.setValue(path);
    CFFuncArguments vp_args;
    vp_args.pushV("path", vp);

    cfmm->pushMessage(FILE_MODULE,
                      FILE_TTF_DIR,
                      CFFuncArguments());
    CFFuncResults re_dir =
    cfmm->pushMessage(FILE_MODULE,
                      FILE_MOVE_TO_TTF_DIR,
                      vp_args);

    /**
     *	2. save attributes to the config file for reload
     */
    QVariant v;
    v.setValue(charcode);
    CFFuncArguments v_args = (CFFuncArguments)re_dir;
    v_args.pushV("charcode", v);

    cfmm->pushMessage(FFT_XML_MODULE,
                      FFT_XML_LOAD,
                      CFFuncArguments());
    cfmm->pushMessage(FFT_XML_MODULE,
                      FFT_XML_PUSH,
                      v_args);

    return CFFuncResults();
}

CFFuncResults
import_code_as_symbol(const CFFuncArguments& args) {
    // save as import_code_as_chars
}


