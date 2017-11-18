#ifndef CFLINEARGRADIENTWIDGET_H
#define CFLINEARGRADIENTWIDGET_H

#include <QWidget>

class CFLinearGradientWidget : public QWidget {

    Q_OBJECT

public:
    explicit CFLinearGradientWidget(QWidget* parent = 0);
    ~CFLinearGradientWidget();

protected:
    void setupUi();

};

#endif // CFLINEARGRADIENTWIDGET_H
