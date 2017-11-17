#ifndef CFIMGWIDGET_H
#define CFIMGWIDGET_H

#include <QWidget>

class CFImgWidget : public QWidget {

    Q_OBJECT

public:
    explicit CFImgWidget(QWidget* parent = 0);
    ~CFImgWidget();

protected:
    void setupUi();
};

#endif // CFIMGWIDGET_H
