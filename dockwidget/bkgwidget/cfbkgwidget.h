#ifndef CFBKGWIDGET_H
#define CFBKGWIDGET_H

#include "../effectwidget/cfeffectwidget.h"

class CFBkgWidget : public CFEffectWidget {

    Q_OBJECT

public:
    explicit CFBkgWidget(QWidget* parent = 0);
    ~CFBkgWidget();

    virtual void setupContent();
    virtual void setControlPanel();

public slots:
    virtual void slot_effectColorChange(const QColor &);
};

#endif // CFBKGWIDGET_H
