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

CFFuncResults CFFuncResults::mergeResult(const CFFuncResults& left,
                                         const CFFuncResults& right) {

    CFFuncResults result;
    result.content = left.content;
    result.content.append(right.content);
    return result;
}
