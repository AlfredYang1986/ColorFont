#ifndef CFBASEMODULE_H
#define CFBASEMODULE_H

#include <QObject>

typedef const QMap<QString, QObject>* (*module_func)(const QMap<QString, QObject>* const);

class CFBaseModule : public QObject {

    Q_OBJECT

protected:
    explicit CFBaseModule();
    ~CFBaseModule();

public:
    const QMap<QString, QObject>*
    pushCommand(const QString& method,
                const QMap<QString, QObject>* const args);

protected:
    QList<std::pair<QString, module_func> > funcs;
};

#endif // CFBASEMODULE_H
