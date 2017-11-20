#ifndef CFBASEMODULE_H
#define CFBASEMODULE_H

#include <QObject>
#include "../../common/funcargs/cfargs.h"

typedef CFFuncResults (*module_func)(const CFFuncArguments&);

class CFBaseModule : public QObject {

    Q_OBJECT

protected:
    explicit CFBaseModule();
    ~CFBaseModule();

public:
    CFFuncResults
    pushCommand(const QString& method,
                const CFFuncArguments& args);

protected:
    QList<std::pair<QString, module_func> > funcs;
};

#endif // CFBASEMODULE_H
