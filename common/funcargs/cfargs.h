#ifndef CFFUNCARGUMENTS_H
#define CFFUNCARGUMENTS_H

#include "../cfpassable.h"
#include "../../errorhandler/cferror.hpp"
#include <QString>
#include <QtOpenGL/QtOpenGL>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {

    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint 	   Advance;    // Offset to advance to next glyph
//    GLuint 	   Height;     // Offset to next line
};

struct exchange_type {
    QString index;
    int cat;
    QString path;
    FT_ULong charcode;
};

Q_DECLARE_METATYPE(Character)
Q_DECLARE_METATYPE(FT_Face)
Q_DECLARE_METATYPE(QVector<FT_ULong>)
Q_DECLARE_METATYPE(QList<exchange_type>*)

class CFFuncArguments : public CFPassable {};

class CFFuncResults : public CFFuncArguments {

public:
    CFFuncResults()
        : _e(0, QString("unknown error")) {}

    const CFError& getLastError() const;
    void resetError(const CFError& e);
    bool isOk() const;

private:
    CFError _e;
};

#endif // CFFUNCARGUMENTS_H
