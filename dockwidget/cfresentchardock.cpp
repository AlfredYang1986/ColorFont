#include "cfresentchardock.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTabWidget>
#include <QWidget>
#include "cfmainwindow.h"
#include "../module/modulemanagement/cfmm.h"

#include "../dialog/fftlibprevwidget/cffftlibprevwidget.h"

CFResentCharDock::CFResentCharDock(QWidget* parent)
    : QDockWidget(parent) {

    setupUi();
    setupFlag();
}

CFResentCharDock::~CFResentCharDock() {

}

void CFResentCharDock::setupUi() {
    view = new QWidget();

    QHBoxLayout* up = new QHBoxLayout();

    search_bar = new QLineEdit();
    up->addWidget(search_bar);

    QVBoxLayout* layout = new QVBoxLayout();
//    tab = new QTabWidget();
    tab = new CFFFTLibPrevWidget();
    tab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addLayout(up);
    layout->addWidget(tab);

    view->setLayout(layout);
    view->setMinimumWidth(300);

    {
        CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
        CFFuncResults reVal = cfmm->pushMessage(QUERY_MODULE, QUERY_MAIN_WINDOW, CFFuncArguments());
        CFMainWindow* w = reVal.getV("main_window").value<CFMainWindow*>();

        QObject::connect(this, SIGNAL(signal_resentPanelClosed()),
                         w, SLOT(slot_resentDockPanelClosed()));
    }
}

void CFResentCharDock::setupFlag() {
    this->setObjectName(tr("resent symbol dock"));
    this->setWidget(view);
    this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
}


void CFResentCharDock::closeEvent(QCloseEvent*) {
    emit signal_resentPanelClosed();
}
