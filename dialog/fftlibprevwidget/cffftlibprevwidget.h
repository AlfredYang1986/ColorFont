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
    void showEvent(QShowEvent *);

    void resetMaxPage();
public slots:
    void slot_pageChanged(int);

private:
    QList<exchange_type>* cur_lst;
    bool _is_connected;
};

#endif // CFFFTLIBPREVWIDGET_H
