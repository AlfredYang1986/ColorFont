#ifndef CFOPERATORWIDGET_H
#define CFOPERATORWIDGET_H

#include <QMdiSubWindow>

class QWidget;

class CFOperatorWidget : public QMdiSubWindow {

    Q_OBJECT

public:
    explicit CFOperatorWidget(QWidget* parent = 0);
    ~CFOperatorWidget();

};

#endif // CFOPERATORWIDGET_H
