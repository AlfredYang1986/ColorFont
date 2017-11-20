#include "cfresentchardock.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTabWidget>
#include <QWidget>

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
    tab = new QTabWidget();
    tab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addLayout(up);
    layout->addWidget(tab);

    view->setLayout(layout);
    view->setMinimumWidth(300);
}

void CFResentCharDock::setupFlag() {
    this->setObjectName(tr("resent symbol dock"));
    this->setWidget(view);
    this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
}
