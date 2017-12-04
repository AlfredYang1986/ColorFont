#ifndef CFFONTLIB_H
#define CFFONTLIB_H

#include "../../module/basemodules/cfbasemodule.h"

class CFModuleManagement;

class CFFontLib : public CFBaseModule {

    Q_OBJECT

protected:
    explicit CFFontLib();

public:
    ~CFFontLib();

    friend class CFModuleManagement;
};


#endif // CFFONTLIB_H
