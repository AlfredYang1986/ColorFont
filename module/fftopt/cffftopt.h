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
    const QVector<std::pair<QString, FT_Face> >& queryOpenedFaces() const;
    QVector<std::pair<QString, FT_Face> >& queryOpenedFaces();

private:
    FT_Library ft;
    QVector<std::pair<QString, FT_Face> > faces;

    friend class CFModuleManagement;
};

#endif // CFFFTOPT_H
