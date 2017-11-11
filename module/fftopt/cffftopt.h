#ifndef CFFFTOPT_H
#define CFFFTOPT_H

#include "../basemodules/cfbasemodule.h"
//#include <ft2build.h>
//#include FT_FREETYPE_H

/**
 * @brief The CFFftOpt class
 * 		load read (only read) ttf files
 */
class CFModuleManagement;

class CFFftOpt : public CFBaseModule {

    Q_OBJECT
protected:
    explicit CFFftOpt();

public:
    ~CFFftOpt();

public:
    void loadTTFFile(const QString& path);

    void loadImage(const QString& path, int index = 0);
    void loadStroke(const QString& path, int index = 0);
};

#endif // CFFFTOPT_H
