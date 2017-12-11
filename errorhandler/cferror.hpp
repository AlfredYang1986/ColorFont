#ifndef CFERROR_H
#define CFERROR_H

#include <QException>

class CFError : public QException {
public:
    CFError(int ec, const QString& str)
        : error_code(ec), error_message(str) {}

    int error_code;
    QString error_message;

    virtual ~CFError() _NOEXCEPT {}
};

#endif // CFERROR_H
