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
            QWidget* parent = 0);
    ~CFImportIndexCell();

protected:
    void setupUi();
    QSize sizeHint() const;

private:
    QLineEdit* edit;
    CFPreviewWidget* widget;

    FT_Face pc;
};

#endif // CFIMPORTINDEXCELL_H
