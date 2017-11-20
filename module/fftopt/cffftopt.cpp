#include "cffftopt.h"
#include <ft2build.h>
#include FT_FREETYPE_H

CFFftOpt::CFFftOpt() {

}

CFFftOpt::~CFFftOpt() {

}

CFFuncResults
CFFftOpt::loadTTFFile(const CFFuncArguments& args) {
    const QVariant& path = args.getV("path");

}

void CFFftOpt::loadImage(const QString& path, int index) {

}

void CFFftOpt::loadStroke(const QString& path, int index) {

}
