#ifndef CFMAINWINDOW_H
#define CFMAINWINDOW_H

#include <QMainWindow>

#include <ft2build.h>
#include FT_FREETYPE_H

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

private slots:

    void on_actionClose_triggered();
    void on_actionSaveAs_triggered();
    void on_actionSave_triggered();
    void on_actionImportTTF_triggered();

    void on_actionOpen_triggered();

    void slot_pushCharacter(FT_Face face, FT_ULong charcode);

private:
    Ui::CFMainWindow *ui;

    CFEffectDock* effect_dock;
    CFResentCharDock* char_dock;

    QMdiArea* area;
};

#endif // CFMAINWINDOW_H
