#include "cfborderwidget.h"

#include <QTabWidget>
#include "../commonwidget/colorbkg/cfcolorbkg.h"
#include "../commonwidget/imgwidget/cfimgwidget.h"
#include "../commonwidget/gradientwidget/cfgradientwidget.h"

CFBorderWidget::CFBorderWidget(QWidget *parent)
    : CFEffectWidget(parent) {

}

CFBorderWidget::~CFBorderWidget() {

}

void CFBorderWidget::setupContent() {
    QWidget* view = new CFColorBkg(this);
    tab->addTab(view, tr("颜色"));

    QWidget* view2 = new CFGradientWidget();
    tab->addTab(view2, tr("渐变"));

    QWidget* view1 = new CFImgWidget();
    tab->addTab(view1, tr("图片"));
}

void CFBorderWidget::setControlPanel() {

}
