#ifndef CFFFTLIBPREVWIDGET_H
#define CFFFTLIBPREVWIDGET_H

#include <QWidget>

#include "../../common/funcargs/cfargs.h"

class CFPreviewWidget;

class CFFFTLibPrevWidget : public QWidget {

    Q_OBJECT

public:
    explicit CFFFTLibPrevWidget(// FT_Face p,
                                QWidget* parent = 0);
    ~CFFFTLibPrevWidget();

protected:
    void setupUi();

public slots:
    void slot_pageChanged(int);

private:
    QList<exchange_type>* cur_lst;
};

#endif // CFFFTLIBPREVWIDGET_H
