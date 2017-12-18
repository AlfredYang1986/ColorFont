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
CFFuncResults import_code_as_chars_lst(const CFFuncArguments& args);
CFFuncResults import_code_as_symbol_lst(const CFFuncArguments& args);
CFFuncResults query_path_from_faces(const CFFuncArguments& args);
CFFuncResults query_path_by_one_face(const CFFuncArguments& args);

CFFftOpt::CFFftOpt() {
    funcs.push_back(std::make_pair(FFT_LOAD_FILE, &loadTTFFile));
    funcs.push_back(std::make_pair(FFT_FREE_FACE, &free_ttf_file));
    funcs.push_back(std::make_pair(FFT_IMPORT_CHAR, &import_code_as_chars));
    funcs.push_back(std::make_pair(FFT_IMPORT_CHAR_LST, &import_code_as_chars_lst));
    funcs.push_back(std::make_pair(FFT_IMPORT_SYMBOL, &import_code_as_symbol));
    funcs.push_back(std::make_pair(FFT_IMPORT_SYMBOL_LST, &import_code_as_symbol_lst));
    funcs.push_back(std::make_pair(FFT_QUERY_PATHS_FROM_FACES, &query_path_from_faces));
    funcs.push_back(std::make_pair(FFT_QUERY_PATH_BY_FACE, &query_path_by_one_face));

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

class path_predicate {
public:
    path_predicate(const QString& p) : _p(p) {}
    bool operator()(const std::pair<QString, FT_Face>& iter) {
        return iter.first == _p;
    }

private:
    QString _p;
};


CFFuncResults
loadTTFFile(const CFFuncArguments& args) {

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFFftOpt* opt = (CFFftOpt*)cfmm->queryModuleInstance(FFT_MODULE);
    FT_Library ft = opt->queryFaceLib();

    const QString& path = args.getV("path").toString();

    QVector<std::pair<QString, FT_Face> >::const_iterator citer =
        std::find_if(opt->faces.begin(), opt->faces.end(), path_predicate(path));

    FT_Face face;
    if (citer == opt->faces.end()) {
        int result = FT_New_Face(ft, path.toStdString().c_str(), 0, &face);
        if (result != 0) {
            qDebug() << "ERROR::FREETYPE: Failed to load font";
        }
        QString p = path;
        opt->faces.push_back(std::make_pair(p, face));

    } else {
        face = (*citer).second;
    }

    CFFuncResults reVal;
    QVariant v(QVariant::UserType);
    v.setValue(face);
    reVal.pushV("face", v);

    opt->queryOpenedFaces().push_back(std::make_pair(path, face));

    return reVal;
}

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

    QVariant v_cat;
    v_cat.setValue(0);
    v_args.pushV("cat", v_cat);

    cfmm->pushMessage(FFT_XML_MODULE,
                      FFT_XML_LOAD,
                      CFFuncArguments());
    cfmm->pushMessage(FFT_XML_MODULE,
                      FFT_XML_PUSH,
                      v_args);

    /**
     * 3. sync doc to file
     */
    cfmm->pushMessage(FFT_XML_MODULE,
                      FFT_XML_SYNC,
                      CFFuncArguments());

    return CFFuncResults();
}

CFFuncResults
import_code_as_symbol(const CFFuncArguments& args) {
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

    QVariant v_cat;
    v_cat.setValue(1);
    v_args.pushV("cat", v_cat);

    cfmm->pushMessage(FFT_XML_MODULE,
                      FFT_XML_LOAD,
                      CFFuncArguments());
    cfmm->pushMessage(FFT_XML_MODULE,
                      FFT_XML_PUSH,
                      v_args);

    /**
     * 3. sync doc to file
     */
    cfmm->pushMessage(FFT_XML_MODULE,
                      FFT_XML_SYNC,
                      CFFuncArguments());

    return CFFuncResults();

}

CFFuncResults
import_code_as_chars_lst(const CFFuncArguments& args) {
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
    cfmm->pushMessage(FFT_XML_MODULE,
                      FFT_XML_LOAD,
                      CFFuncArguments());

    QVector<FT_ULong> vec_chars = args.getV("char-lst").value<QVector<FT_ULong> >();

    QVector<FT_ULong>::const_iterator iter = vec_chars.begin();
    while (iter != vec_chars.end()) {
        FT_ULong charcode = *iter;

        CFFuncArguments v_args = (CFFuncArguments)re_dir;

        QVariant v;
        v.setValue(charcode);
        v_args.pushV("charcode", v);

        QVariant v_cat;
        v_cat.setValue(0);
        v_args.pushV("cat", v_cat);

        cfmm->pushMessage(FFT_XML_MODULE,
                          FFT_XML_PUSH,
                          v_args);

        ++iter;
    }

    /**
     * 3. sync doc to file
     */
    cfmm->pushMessage(FFT_XML_MODULE,
                      FFT_XML_SYNC,
                      CFFuncArguments());

    return CFFuncResults();
}

CFFuncResults
import_code_as_symbol_lst(const CFFuncArguments& args) {
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
    cfmm->pushMessage(FFT_XML_MODULE,
                      FFT_XML_LOAD,
                      CFFuncArguments());

    QVector<FT_ULong> vec_chars = args.getV("char-lst").value<QVector<FT_ULong> >();

    QVector<FT_ULong>::const_iterator iter = vec_chars.begin();
    while (iter != vec_chars.end()) {
        FT_ULong charcode = *iter;

        CFFuncArguments v_args = (CFFuncArguments)re_dir;

        QVariant v;
        v.setValue(charcode);
        v_args.pushV("charcode", v);

        QVariant v_cat;
        v_cat.setValue(1);
        v_args.pushV("cat", v_cat);

        cfmm->pushMessage(FFT_XML_MODULE,
                          FFT_XML_PUSH,
                          v_args);

        ++iter;
    }

    /**
     * 3. sync doc to file
     */
    cfmm->pushMessage(FFT_XML_MODULE,
                      FFT_XML_SYNC,
                      CFFuncArguments());

    return CFFuncResults();

}

CFFuncResults query_path_from_faces(const CFFuncArguments& args) {
    QVector<FT_Face> faces = args.getV("faces").value<QVector<FT_Face> >();

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFFftOpt* opt = (CFFftOpt*)cfmm->queryModuleInstance(FFT_MODULE);
    QVector<std::pair<QString, FT_Face> > opend_faces = opt->queryOpenedFaces();

    QVector<QString> paths;
    QVector<FT_Face>::const_iterator iter = faces.begin();
    while (iter != faces.end()) {
        FT_Face f = *iter;

        QVector<std::pair<QString, FT_Face> >::iterator i =
            std::find_if(opend_faces.begin(), opend_faces.end(), face_predicate(f));

        if (i != opend_faces.end()) {
            paths.push_back((*i).first);
        }

        ++iter;
    }

   CFFuncResults reVal;
   QVariant v;
   v.setValue(paths);
   reVal.pushV("paths", v);

   return reVal;
}


CFFuncResults query_path_by_one_face(const CFFuncArguments& args) {
    FT_Face face = args.getV("face").value<FT_Face>();

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFFftOpt* opt = (CFFftOpt*)cfmm->queryModuleInstance(FFT_MODULE);
    QVector<std::pair<QString, FT_Face> > opend_faces = opt->queryOpenedFaces();

    QVector<std::pair<QString, FT_Face> >::iterator i =
        std::find_if(opend_faces.begin(), opend_faces.end(), face_predicate(face));

    CFFuncResults reVal;
    QVariant v;
    v.setValue((*i).first);
    reVal.pushV("path", v);

    return reVal;

}
