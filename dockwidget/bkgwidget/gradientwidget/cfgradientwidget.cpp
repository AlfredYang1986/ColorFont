#include "cfgradientwidget.h"
#include "lineargradientwidget/cflineargradientwidget.h"

#include <QHBoxLayout>
#include <QTabWidget>

CFGradientWidget::CFGradientWidget(QWidget* parent)
    : QWidget(parent) {

    setupUi();
}

CFGradientWidget::~CFGradientWidget() {

}

void CFGradientWidget::setupUi() {
     QHBoxLayout* layout = new QHBoxLayout();

     tab = new QTabWidget();
     tab->addTab(new CFLinearGradientWidget(), tr("线性"));

     layout->addWidget(tab);

     this->setLayout(layout);
}
