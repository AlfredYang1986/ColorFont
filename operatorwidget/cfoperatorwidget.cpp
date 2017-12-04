#include "cfoperatorwidget.h"
#include <QWidget>

CFOperatorWidget::CFOperatorWidget(QWidget *parent)
    : QMdiSubWindow(parent) {

    this->resize(800, 400);
    this->setStyleSheet("backgrund-color : red");
}

CFOperatorWidget::~CFOperatorWidget() {

}
