#ifndef CFERRORHANDLER_H
#define CFERRORHANDLER_H

#include <QObject>
#include <QList>
#include "cferror.hpp"

class CFErrorHandler : public QObject {

    Q_OBJECT
protected:
    explicit CFErrorHandler();

public:
    static const CFErrorHandler* queryInstance();
    const CFError triggleError(int code) const;

private:
    static CFErrorHandler* instance;

    QList<CFError> errors;
};

#endif // CFERRORHANDLER_H
