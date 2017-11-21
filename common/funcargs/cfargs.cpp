#include "cfargs.h"

const CFError& CFFuncResults::getLastError() const {
    return _e;
}

void CFFuncResults::resetError(const CFError& e) {
    _e = e;
}

bool CFFuncResults::isOk() const {
    return _e.error_code == 0;
}
