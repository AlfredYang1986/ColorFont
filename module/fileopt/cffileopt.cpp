#include "cffileopt.h"
#include <QList>
#include <QDebug>
#include <QMap>
#include "../../common/funcargs/cfargs.h"
#include <QFile>
#include <QDir>

static const QString TTF_PATH = "/ttf_dir";

CFFuncResults
create_ttf_dir(const CFFuncArguments& args);
CFFuncResults
move_2_ttf_dir(const CFFuncArguments& args);

CFFileOpt::CFFileOpt() {
    funcs = {
        std::make_pair(FILE_TTF_DIR, &create_ttf_dir),
        std::make_pair(FILE_MOVE_TO_TTF_DIR, &move_2_ttf_dir)
    };
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

    QVariant v;
    if (QFile::copy(ori_path, dst_path + "/test.ttf")) {
        v.setValue(true);
    } else {
        v.setValue(false);
    }

    CFFuncResults reVal;
    reVal.pushV("result", v);

    return reVal;
}
