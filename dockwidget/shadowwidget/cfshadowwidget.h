#ifndef CFSHADOWWIDGET_H
#define CFSHADOWWIDGET_H

#include "../effectwidget/cfeffectwidget.h"

class QLabel;
class QLineEdit;

class CFShadowWidget : public CFEffectWidget {

    Q_OBJECT

public:
    explicit CFShadowWidget(QWidget* parent = 0);
    ~CFShadowWidget();

    virtual void setupContent();
    virtual void setControlPanel();

};

#endif // CFSHADOWWIDGET_H
