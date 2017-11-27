#ifndef CFFILEOPT_H
#define CFFILEOPT_H

#include "../basemodules/cfbasemodule.h"
#include "../../module/modulemanagement/cfmm.h"

/**
 * @brief The CFFileOpt class
 * 		save load and resent list
 */

class CFModuleManagement;

class CFFileOpt : public CFBaseModule {

    Q_OBJECT
protected:
    explicit CFFileOpt();

public:
    ~CFFileOpt();

public:


    void saveToPath(const QString& path);
    void* loadFromPath(const QString& path);
    const QList<QString> resentPathLst() const;
    const QString getResentFilePath() const;

//    const QMap<QString, QObject>*
//    open_test(const QMap<QString, QObject>&);

    friend class CFModuleManagement;
};

#endif // CFFILEOPT_H
