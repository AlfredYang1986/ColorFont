#include "cflineargradientwidget.h"

CFLinearGradientWidget::CFLinearGradientWidget(QWidget *parent)
    : QWidget(parent) {

    setupUi();
}

CFLinearGradientWidget::~CFLinearGradientWidget() {

}

void CFLinearGradientWidget::setupUi() {
    this->setMinimumSize(100, 100);
}
