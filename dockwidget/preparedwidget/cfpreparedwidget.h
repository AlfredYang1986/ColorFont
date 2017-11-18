#ifndef CFPREPAREDWIDGET_H
#define CFPREPAREDWIDGET_H

#include "../effectwidget/cfeffectwidget.h"

class QTableView;

class CFPreparedWidget : public CFEffectWidget {

    Q_OBJECT

public:
    explicit CFPreparedWidget(QWidget* parent = 0);
    ~CFPreparedWidget();

    virtual void setupContent();
    virtual void setControlPanel();

private:
    QTableView* table;
};

#endif // CFPREPAREDWIDGET_H
