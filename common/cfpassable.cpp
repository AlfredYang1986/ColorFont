#include "cfpassable.h"
#include <QDebug>

class key_perdicate {

public:
    key_perdicate(const QString& key) : _key(key) {}
    bool
    operator()(const std::pair<QString, QVariant>& iter) {
        return iter.first == _key;
    }

private:
    QString _key;
};

const QVariant&
CFPassable::getV(const QString& name) const {
    QList<std::pair<QString, QVariant> >::const_iterator citer =
            std::find_if(content.begin(), content.end(), key_perdicate(name));

    if (citer != content.end())
        return (*citer).second;
    else return QVariant();
}

void
CFPassable::pushV(
        const QString& name,
        const QVariant& value) {

    QList<std::pair<QString, QVariant> >::iterator iter =
            std::find_if(content.begin(), content.end(), key_perdicate(name));

    if (iter == content.end()) {
        content.push_back(std::make_pair(name, value));
    } else {
        (*iter).second = value;
    }
}
