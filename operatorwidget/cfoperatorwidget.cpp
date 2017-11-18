#include "cfoperatorwidget.h"
#include <QWidget>

CFOperatorWidget::CFOperatorWidget(QWidget *parent)
    : QMdiSubWindow(parent) {

    this->resize(300, 300);
    this->setStyleSheet("backgrund-color : red");
}

CFOperatorWidget::~CFOperatorWidget() {

}
