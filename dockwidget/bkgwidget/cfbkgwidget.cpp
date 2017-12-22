#include "cfbkgwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTabWidget>
#include "../commonwidget/colorbkg/cfcolorbkg.h"
#include "../commonwidget/imgwidget/cfimgwidget.h"
#include "../commonwidget/gradientwidget/cfgradientwidget.h"
#include "cfmainwindow.h"
#include "module/modulemanagement/cfmm.h"

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

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFFuncResults result = cfmm->pushMessage(QUERY_MODULE, QUERY_MAIN_WINDOW, CFFuncArguments());
    CFMainWindow* w = result.getV("main_window").value<CFMainWindow*>();

    QObject::connect(this, SIGNAL(signal_effectColorChanged(QColor, int)),
                     w, SLOT(slot_dockColorChanged(QColor, int)));
}

void CFBkgWidget::setControlPanel() {
    // do nothing ...
}

void CFBkgWidget::slot_effectColorChange(const QColor& color) {
    emit signal_effectColorChanged(color, FILL_BKG);
}
