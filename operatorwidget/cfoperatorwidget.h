#ifndef CFOPERATORWIDGET_H
#define CFOPERATORWIDGET_H

#include <QMdiSubWindow>

class QWidget;
class CFGLLineWidget;

class CFOperatorWidget : public QMdiSubWindow {

    Q_OBJECT

public:
    explicit CFOperatorWidget(QWidget* parent = 0);
    ~CFOperatorWidget();

protected:
    void setupUi();

private:
    QVector<CFGLLineWidget*> contents;
};

#endif // CFOPERATORWIDGET_H
