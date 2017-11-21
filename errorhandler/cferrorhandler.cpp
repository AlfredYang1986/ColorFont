#include "cferrorhandler.h"
#include <algorithm>

CFErrorHandler* CFErrorHandler::instance = NULL;

const CFErrorHandler* CFErrorHandler::queryInstance() {
    if (instance == NULL) {
        instance = new CFErrorHandler();
    }

    Q_ASSERT(instance != NULL);
    return instance;
}

CFErrorHandler::CFErrorHandler() {
    errors = {
        CFError(0, "No Error"),
        CFError(1, "File not Exist"),
        CFError(2, "Unknown error")
    };
}

class error_predicate {
public:
    error_predicate(int code) : _code(code) {}

    bool operator()(const CFError& e) {
        return _code == e.error_code;
    }

private:
    int _code;
};

const CFError& CFErrorHandler::triggleError(int code) const {
    QList<CFError>::const_iterator iter =
            std::find_if(errors.begin(), errors.end(), error_predicate(code));

    if (iter != errors.end()) {
        return (*iter);

    } else exit(1);
}
