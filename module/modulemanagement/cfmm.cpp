#include "cfmm.h"
#include "../basemodules/cfbasemodule.h"
#include <algorithm>
#include <QException>
#include "../fileopt/cffileopt.h"
using namespace std;

CFModuleManagement* CFModuleManagement::instance = NULL;

const CFModuleManagement* CFModuleManagement::queryInstance() {
    if (instance == NULL) {
        instance = new CFModuleManagement();
    }

    Q_ASSERT(instance != NULL);
    return instance;
}

CFModuleManagement::CFModuleManagement() {
    this->initCFModules();
}

CFModuleManagement::~CFModuleManagement() {
    this->destoryCFModules();
}

void CFModuleManagement::initCFModules() {
    mms = {
        std::make_pair("fileOpt", new CFFileOpt())
    };
}

void CFModuleManagement::destoryCFModules() {

}

CFBaseModule* CFModuleManagement::queryModuleInstance() const {
    return NULL;
}

class module_predicate {
public:
    module_predicate(const QString& pred) : _pred(pred) {}

    bool operator()(const std::pair<QString, CFBaseModule*>& iter) {
        return _pred == iter.first;
    }

private:
    QString _pred;
};

const QMap<QString, QObject>*
CFModuleManagement::pushMessage(const QString& module,
                                const QString& method,
                                const QMap<QString, QObject>& args) {

    QList<std::pair<QString, CFBaseModule*> >::iterator iter =
        std::find_if(mms.begin(), mms.end(), module_predicate(module));

    if (iter != mms.end()) {
        CFBaseModule* cfm = iter->second;
        return cfm->pushCommand(method, args);

    } else {
        // TODO: 出现错误写法
        exit(1);
    }
}
