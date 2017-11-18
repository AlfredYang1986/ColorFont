#ifndef CFBORDERWIDGET_H
#define CFBORDERWIDGET_H

#include "../effectwidget/cfeffectwidget.h"

class QWidget;

class CFBorderWidget : public CFEffectWidget {

    Q_OBJECT

public:
    explicit CFBorderWidget(QWidget* parent = 0);
    ~CFBorderWidget();

    virtual void setupContent();
    virtual void setControlPanel();
};

#endif // CFBORDERWIDGET_H
