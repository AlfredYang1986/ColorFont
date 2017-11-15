#ifndef CFEFFECTWIDGET_H
#define CFEFFECTWIDGET_H

#include <QWidget>

class QTabWidget;
class QPushButton;
class QHBoxLayout;

class CFEffectWidget : public QWidget {

    Q_OBJECT

public:
    explicit CFEffectWidget(QWidget* parent = 0);
    ~CFEffectWidget();

    virtual void setupUi();
    virtual void setupContent() = 0;
    virtual void setControlPanel() = 0;
    virtual QPushButton* setClearBtn();

protected:
    QTabWidget* tab;
    QWidget* panel;
};

#endif // CFEFFECTWIDGET_H
