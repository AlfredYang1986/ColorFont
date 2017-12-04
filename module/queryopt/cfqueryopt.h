#ifndef CFQUERYOPT_H
#define CFQUERYOPT_H

#include "../basemodules/cfbasemodule.h"
#include "../../module/modulemanagement/cfmm.h"

class CFModuleManagement;
class CFMainWindow;

class CFQueryOpt : public CFBaseModule {

    Q_OBJECT

protected:
    explicit CFQueryOpt();

public:
    ~CFQueryOpt();

    CFMainWindow* main_window;

    friend class CFModuleManagement;
};

#endif // CFQUERYOPT_H
