#include "cffileopt.h"
#include <QList>
#include <QDebug>
#include <QMap>

const QMap<QString, QObject>*
open_test(const QMap<QString, QObject>* const args) {
    qDebug() << "debug chians of response" ;
//    QMap<QString, QObject>::const_iterator iter = args->begin();
//    while(iter != args->end()) {
//        qDebug() << "result key is : " << iter.key()
//                 << endl;
//    }

    return new QMap<QString, QObject>();
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


