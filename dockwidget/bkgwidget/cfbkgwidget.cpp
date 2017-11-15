#include "cfbkgwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTabWidget>
#include "colorbkg/cfcolorbkg.h"

CFBkgWidget::CFBkgWidget(QWidget *parent)
    : CFEffectWidget(parent) {

}

CFBkgWidget::~CFBkgWidget() {

}

void CFBkgWidget::setupContent() {
    QWidget* view = new CFColorBkg();
    tab->addTab(view, tr("颜色"));
}

void CFBkgWidget::setControlPanel() {
    // do nothing ...
}
