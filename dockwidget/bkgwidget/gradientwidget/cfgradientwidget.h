#ifndef CFGRADIENTWIDGET_H
#define CFGRADIENTWIDGET_H

#include <QWidget>

class QTabWidget;

class CFGradientWidget : public QWidget {

    Q_OBJECT

public:
    explicit CFGradientWidget(QWidget* parent = 0);
    ~CFGradientWidget();

protected:
    void setupUi();

private:
    QTabWidget* tab;
};

#endif // CFGRADIENTWIDGET_H
