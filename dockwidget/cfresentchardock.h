#ifndef CFRESENTSYMBOLDOCK_H
#define CFRESENTSYMBOLDOCK_H

#include <QDockWidget>

class QWidget;
class QTabWidget;
class QLineEdit;

class CFResentCharDock : public QDockWidget {

    Q_OBJECT

public:
    explicit CFResentCharDock(QWidget* parent = 0);
    ~CFResentCharDock();

protected:
    void setupUi();
    void setupFlag();

private:
    QWidget* view;
    QTabWidget* tab;
    QLineEdit* search_bar;
};

#endif // CFRESENTSYMBOLDOCK_H
