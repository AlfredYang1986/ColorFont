#ifndef CFFILLWIDGET_H
#define CFFILLWIDGET_H

#include "../effectwidget/cfeffectwidget.h"

class QWidget;

class CFFillWidget : public CFEffectWidget {

    Q_OBJECT

public:
    explicit CFFillWidget(QWidget* parent = 0);
    ~CFFillWidget();

    virtual void setupContent();
    virtual void setControlPanel();

public slots:
    virtual void slot_effectColorChange(const QColor &);
};

#endif // CFFILLWIDGET_H
