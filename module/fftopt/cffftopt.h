#ifndef CFFFTOPT_H
#define CFFFTOPT_H

#include "../basemodules/cfbasemodule.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "common/funcargs/cfargs.h"

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

    FT_Library queryFaceLib();

public:
//    CFFuncResults loadTTFFile(const CFFuncArguments& args);

    void loadImage(const QString& path, int index = 0);
    void loadStroke(const QString& path, int index = 0);

private:
    FT_Library ft;
    QList<FT_Face> faces;

    friend class CFModuleManagement;
};

#endif // CFFFTOPT_H
