#ifndef CFPASSABLE_H
#define CFPASSABLE_H

#include <QList>
#include <QString>
#include <QVariant>

class CFPassable {

public:
    CFPassable() {}

    const QVariant& getV(const QString& name) const;
    void pushV(const QString& name, const QVariant& value);

protected:
    QList<std::pair<QString, QVariant> > content;
};

#endif // CFPASSABLE_H
