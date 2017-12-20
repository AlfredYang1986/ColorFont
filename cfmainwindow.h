#ifndef CFMAINWINDOW_H
#define CFMAINWINDOW_H

#include <QMainWindow>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "dockwidget/effectwidget/cfeffectwidget.h"

class CFEffectDock;
class CFResentCharDock;
class QMdiArea;

namespace Ui {
class CFMainWindow;
}

class CFMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CFMainWindow(QWidget *parent = 0);
    ~CFMainWindow();

    void setupEffectDock();
    void setupResentSymbolDock();

private slots:

    void on_actionClose_triggered();
    void on_actionSaveAs_triggered();
    void on_actionSave_triggered();
    void on_actionImportTTF_triggered();

    void on_actionOpen_triggered();

    void slot_pushCharacter(FT_Face face, FT_ULong charcode);
    void slot_refreshCharacters();
    void slot_resentDockPanelClosed();
    void slot_controlPanelClosed();

    void slot_dockColorChanged(const QColor& color, int e);

    void on_actionBrandNew_triggered();

private:
    Ui::CFMainWindow *ui;

    CFEffectDock* effect_dock;
    CFResentCharDock* char_dock;

    QMdiArea* area;
};

#endif // CFMAINWINDOW_H
