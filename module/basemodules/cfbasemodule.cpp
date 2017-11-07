#include "cfbasemodule.h"
#include <algorithm>
#include <QMap>
#include <QException>
using namespace std;

CFBaseModule::CFBaseModule() {

}

CFBaseModule::~CFBaseModule() {

}

class method_predicate {
public:
    method_predicate(const QString& pred) : _pred(pred) {}

    bool operator()(const std::pair<QString, module_func>& iter) {
        return _pred == iter.first;
    }

private:
    QString _pred;
};

const QMap<QString, QObject>
CFBaseModule::pushCommand(const QString& method,
                          const QMap<QString, QObject>& args) {


    QList<std::pair<QString, module_func> >::iterator iter =
            std::find_if(funcs.begin(), funcs.end(), method_predicate(method));

    if (iter != func.end()) {
        module_func f = iter->second();
        return f(args);
    } else throw new QException("出现错误");
}
