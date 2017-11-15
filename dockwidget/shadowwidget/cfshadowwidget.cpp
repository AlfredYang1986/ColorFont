#include "cfshadowwidget.h"
#include <QTabWidget>
#include "../effectwidget/cfeffectwidget.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

CFShadowWidget::CFShadowWidget(QWidget *parent)
    : CFEffectWidget(parent) {

}

CFShadowWidget::~CFShadowWidget() {

}

void CFShadowWidget::setupContent() {
    QWidget* view = new QWidget();
    view->setFixedWidth(150);

    QHBoxLayout* layout = new QHBoxLayout();
    QLabel* label = new QLabel(tr("角度: "));
    layout->addWidget(label);

    QLineEdit* le = new QLineEdit();
    layout->addWidget(le);
    view->setLayout(layout);

    tab->addTab(view, tr("阴影"));
}

void CFShadowWidget::setControlPanel() {
    // do nothing ...
}
