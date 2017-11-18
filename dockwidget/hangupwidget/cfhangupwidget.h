#ifndef CFHANGUPWIDGET_H
#define CFHANGUPWIDGET_H

#include "../effectwidget/cfeffectwidget.h"

class QHBoxLayout;
class QGridLayout;
class QLineEdit;
class QLabel;

class CFHangupWidget : public CFEffectWidget {

    Q_OBJECT

public:
    explicit CFHangupWidget(QWidget* parent = 0);
    ~CFHangupWidget();

    virtual void setupContent();
    virtual void setControlPanel();

private:
    QHBoxLayout* createInputProperty(const QString& des, QLineEdit** edit);
    QGridLayout* createRightInputPanel();
private:
    QLabel* pic_prev;
    QLineEdit* x;
    QLineEdit* y;
//    QLineEdit* a;
    QLineEdit* w;
    QLineEdit* h;
};

#endif // CFHANGUPWIDGET_H
