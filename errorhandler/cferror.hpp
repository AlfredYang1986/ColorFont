#ifndef CFERROR_H
#define CFERROR_H

#include <QException>

class CFError : public QException {

private:
    int error_code;
    QString error_message;
};

#endif // CFERROR_H
