#ifndef CFRESENTSYMBOLDOCK_H
#define CFRESENTSYMBOLDOCK_H

#include <QDockWidget>

class QWidget;
class QTabWidget;
class QLineEdit;

class CFFFTLibPrevWidget;

class CFResentCharDock : public QDockWidget {

    Q_OBJECT

public:
    explicit CFResentCharDock(QWidget* parent = 0);
    ~CFResentCharDock();

signals:
    void signal_resentPanelClosed();

protected:
    void setupUi();
    void setupFlag();

    void closeEvent(QCloseEvent*);

private:
    QWidget* view;
    QLineEdit* search_bar;
    CFFFTLibPrevWidget* tab;
};

#endif // CFRESENTSYMBOLDOCK_H
