#ifndef CFIMPORTINDEXCELL_H
#define CFIMPORTINDEXCELL_H

#include <QWidget>

#include "../../common/funcargs/cfargs.h"

class QLineEdit;
class CFPreviewWidget;
class QMenu;

class CFImportIndexCell : public QWidget {

    Q_OBJECT

public:
    explicit CFImportIndexCell(QWidget* parent = 0);

    explicit CFImportIndexCell(
            FT_Face p,
            FT_ULong ccd,
            QWidget* parent = 0);
    ~CFImportIndexCell();

    void resetCurrentUUID(const QString& str);
    void resetFace(FT_Face face);
    void resetCharcode(FT_ULong code);
    void repaintOpenGL();
//    CFPreviewWidget* getContentWidget() const;

signals:
    void signal_pressed(FT_Face face, FT_ULong charcode);

public slots:
    void slot_importCodeAsChar();
    void slot_importCodeAsSymbol();

protected:
    void setupUi();
    void contextMenuEvent(QContextMenuEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QMenu* m;
    QGLContext* context;
    QLineEdit* edit;
    CFPreviewWidget* w;
    FT_Face pc;
    FT_ULong charcode;

    QString uuid;
};

#endif // CFIMPORTINDEXCELL_H
