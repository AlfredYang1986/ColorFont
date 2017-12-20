#include "cfbkgwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTabWidget>
#include "../commonwidget/colorbkg/cfcolorbkg.h"
#include "../commonwidget/imgwidget/cfimgwidget.h"
#include "../commonwidget/gradientwidget/cfgradientwidget.h"

CFBkgWidget::CFBkgWidget(QWidget *parent)
    : CFEffectWidget(parent) {

}

CFBkgWidget::~CFBkgWidget() {

}

void CFBkgWidget::setupContent() {
    QWidget* view = new CFColorBkg(this);
    tab->addTab(view, tr("颜色"));

    QWidget* view2 = new CFGradientWidget();
    tab->addTab(view2, tr("渐变"));

    QWidget* view1 = new CFImgWidget();
    tab->addTab(view1, tr("图片"));
}

void CFBkgWidget::setControlPanel() {
    // do nothing ...
}
