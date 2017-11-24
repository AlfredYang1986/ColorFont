#ifndef CFIMPORTINDEXCELL_H
#define CFIMPORTINDEXCELL_H

#include <QWidget>

#include "../../common/funcargs/cfargs.h"

class QLineEdit;
class CFPreviewWidget;

class CFImportIndexCell : public QWidget {

    Q_OBJECT

public:
    explicit CFImportIndexCell(
            FT_Face p,
            FT_ULong ccd,
            QWidget* parent = 0);
    ~CFImportIndexCell();

    void resetCharcode(FT_ULong code);
    void repaintOpenGL();
protected:
    void setupUi();
    QSize sizeHint() const;

private:
    QLineEdit* edit;
    CFPreviewWidget* w;
    FT_Face pc;
    FT_ULong charcode;
};

#endif // CFIMPORTINDEXCELL_H
