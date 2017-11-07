#ifndef CFMM_H
#define CFMM_H

#include <QObject>
#include <QMap>

class CFBaseModule;

class CFModuleManagement : public QObject {

    Q_OBJECT

protected:
    explicit CFModuleManagement();

public:
    static const CFModuleManagement* queryInstance();
    ~CFModuleManagement();

public:
    void initCFModules();
    void destoryCFModules();

    CFBaseModule* queryModuleInstance() const;
    const QMap<QString, QObject>*
    pushMessage(const QString& module,
                const QString& method,
                const QMap<QString, QObject>& args);

private:
    static CFModuleManagement* instance;

    QList<std::pair<QString, CFBaseModule*> > mms;
};

#endif // CFMM_H
