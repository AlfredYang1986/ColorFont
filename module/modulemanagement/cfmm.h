#ifndef CFMM_H
#define CFMM_H

#include <QObject>
#include <QMap>
#include "../../common/funcargs/cfargs.h"

class CFBaseModule;

class CFModuleManagement : public QObject {

    Q_OBJECT

protected:
    explicit CFModuleManagement();

public:
    static CFModuleManagement* queryInstance();
    ~CFModuleManagement();

public:
    void initCFModules();
    void destoryCFModules();

    CFBaseModule* queryModuleInstance() const;

    CFFuncResults
    pushMessage(const QString& module,
                const QString& method,
                const CFFuncArguments& args);

private:
    static CFModuleManagement* instance;

    QList<std::pair<QString, CFBaseModule*> > mms;
};

#endif // CFMM_H
