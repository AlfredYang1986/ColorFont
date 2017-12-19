#include "cffileopt.h"
#include <QList>
#include <QDebug>
#include <QMap>
#include "../../common/funcargs/cfargs.h"
#include <QFile>
#include <QDir>
#include <QUuid>

static const QString TTF_PATH = "/ttf_dir";
static const QString RESOURCE_PATH = "/resource_dir";

CFFuncResults
create_ttf_dir(const CFFuncArguments& args);
CFFuncResults
move_2_ttf_dir(const CFFuncArguments& args);

CFFuncResults
create_save_dir(const CFFuncArguments& args);
CFFuncResults
move_2_dist_dir(const CFFuncArguments& args);
CFFuncResults
check_save_dir(const CFFuncArguments& args);

CFFileOpt::CFFileOpt() {
    funcs.push_back(std::make_pair(FILE_TTF_DIR, &create_ttf_dir));
    funcs.push_back(std::make_pair(FILE_MOVE_TO_TTF_DIR, &move_2_ttf_dir));
    funcs.push_back(std::make_pair(FILE_SAVE_DIR, &create_save_dir));
    funcs.push_back(std::make_pair(FILE_CHECK_SAVE_DIR, &check_save_dir));
}

CFFileOpt::~CFFileOpt() {

}

void CFFileOpt::saveToPath(const QString &path) {

}

void* CFFileOpt::loadFromPath(const QString &path) {
    return NULL;
}

const QList<QString> CFFileOpt::resentPathLst() const {
    return QList<QString>();
}

const QString CFFileOpt::getResentFilePath() const {
    return "";
}

CFFuncResults
create_ttf_dir(const CFFuncArguments &) {
    QDir dir;
    QString path = QCoreApplication::applicationDirPath() + TTF_PATH;

    if (!dir.exists(path)) {
        dir.mkdir(path);
        qDebug() << "create a ttf dir";
    } else {
        qDebug() << "ttf dir already exists";
    }

    return CFFuncResults();
}

CFFuncResults
move_2_ttf_dir(const CFFuncArguments &args) {

    QString ori_path = args.getV("path").value<QString>();
    QString dst_path = QCoreApplication::applicationDirPath() + TTF_PATH;

    QUuid id = QUuid::createUuid();
    QString strId = dst_path + "/" + id.toString().replace('{', "").replace('}', "") + ".ttf";

    if (!QFile(strId).exists()) {
        QFile::copy(ori_path, strId);
    }

    CFFuncResults reVal;
    QVariant v;
    v.setValue(strId);
    reVal.pushV("path", v);

    return reVal;
}

CFFuncResults
create_save_dir(const CFFuncArguments& args) {

    /**
     * dir
     */
    QDir dir;
    QString save_path = args.getV("save_path").value<QString>();
    if (!dir.exists(save_path)) {
        dir.mkdir(save_path);
    }

    /**
     * ttf dir
     */
    QString save_ttf_dir = save_path + TTF_PATH;
    if (!dir.exists(save_ttf_dir)) {
        dir.mkdir(save_ttf_dir);
    }

    /**
     * resource dir
     */
    QString save_resource_dir = save_path + RESOURCE_PATH;
    if (!dir.exists(save_resource_dir)) {
        dir.mkdir(save_resource_dir);
    }

    return CFFuncResults();
}

CFFuncResults
move_2_dist_dir(const CFFuncArguments& args) {

}

CFFuncResults
check_save_dir(const CFFuncArguments &args) {
    QString path = args.getV("path").value<QString>();

    QDir dir;
    QString save_dir = path.left(path.lastIndexOf("/"));
    if (!dir.exists(save_dir)) {
        qDebug() << "save file is not exists";
        exit(1);
    }

    QString save_ttf_dir = save_dir + TTF_PATH;
    if (!dir.exists(save_ttf_dir)) {
        qDebug() << "save ttf file is not exists";
        exit(1);
    }

    QString save_resource_dir = save_dir + RESOURCE_PATH;
    if (!dir.exists(save_resource_dir)) {
        qDebug() << "save resources file is not exists";
        exit(1);
    }

    return CFFuncResults();
}
