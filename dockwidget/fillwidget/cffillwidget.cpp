#include "cffillwidget.h"

#include <QTabWidget>
#include "../commonwidget/colorbkg/cfcolorbkg.h"
#include "../commonwidget/imgwidget/cfimgwidget.h"
#include "../commonwidget/gradientwidget/cfgradientwidget.h"

CFFillWidget::CFFillWidget(QWidget *parent)
    : CFEffectWidget(parent) {

}

CFFillWidget::~CFFillWidget() {

}

void CFFillWidget::setupContent() {
    QWidget* view = new CFColorBkg();
    tab->addTab(view, tr("颜色"));

    QWidget* view2 = new CFGradientWidget();
    tab->addTab(view2, tr("渐变"));

    QWidget* view1 = new CFImgWidget();
    tab->addTab(view1, tr("图片"));
}

void CFFillWidget::setControlPanel() {

}
