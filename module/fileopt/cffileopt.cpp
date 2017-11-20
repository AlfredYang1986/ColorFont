#include "cffileopt.h"
#include <QList>
#include <QDebug>
#include <QMap>
#include "../../common/funcargs/cfargs.h"

CFFuncResults
open_test(const CFFuncArguments& args) {
    qDebug() << "debug chians of response" ;
//    QMap<QString, QObject>::const_iterator iter = args->begin();
//    while(iter != args->end()) {
//        qDebug() << "result key is : " << iter.key()
//                 << endl;
//    }

    return CFFuncResults();
}

CFFileOpt::CFFileOpt() {
    funcs.append(std::make_pair(QString("open"), &open_test));
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


