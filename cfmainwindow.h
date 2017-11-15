#ifndef CFMAINWINDOW_H
#define CFMAINWINDOW_H

#include <QMainWindow>

class CFEffectDock;

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
    void on_actionOpenFont_triggered();

    void on_actionClose_triggered();

    void on_actionSaveAs_triggered();

    void on_actionSave_triggered();

private:
    Ui::CFMainWindow *ui;

    CFEffectDock* effect_dock;
};

#endif // CFMAINWINDOW_H
