#ifndef CFXMLOPT_H
#define CFXMLOPT_H

#include "../../module/modulemanagement/cfmm.h"
#include "../../module/basemodules/cfbasemodule.h"

class QDomDocument;

class CFXMLOpt : public CFBaseModule {

    Q_OBJECT

protected:
    explicit CFXMLOpt();

public:
    ~CFXMLOpt();

    bool init_config();

    QDomDocument* doc;
    QFile* file;
    QList<std::pair<std::pair<QString, int>,
            std::pair<QString, FT_ULong> > > lst;
private:
    QString path;

    friend class CFModuleManagement;
};

#endif // CFXMLOPT_H
