#include "cfeffectwidget.h"
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>

CFEffectWidget::CFEffectWidget(QWidget* parent)
    : QWidget(parent) {

    setupUi();
}

CFEffectWidget::~CFEffectWidget() {

}

void CFEffectWidget::setupUi() {
    QVBoxLayout* layout = new QVBoxLayout();

    tab = new QTabWidget();
    tab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//    QStyle* s = new QStyle();

//    this->setStyleSheet(
//                "QTabWidget:tab {"
//                    "background-color: transparent;"
//                    "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
//                                                 "stop: 0 rgba(255,255,255,0),"
//                                                 "stop: 1.0 rgba(255, 255, 255, 120));"
//                "}"
//                );

    panel = new QWidget();
    panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QWidget* clear_panel = new QWidget();
    QHBoxLayout* clear_panel_layout = new QHBoxLayout();
    QPushButton* btn = this->setClearBtn();
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    clear_panel_layout->addWidget(btn);
    clear_panel->setLayout(clear_panel_layout);

    layout->addWidget(tab);
    layout->addWidget(panel);
    layout->addWidget(clear_panel);
    layout->addSpacerItem(
                new QSpacerItem(0, 0,
                                QSizePolicy::Fixed, QSizePolicy::Expanding));

    this->setLayout(layout);
    this->setBackgroundRole(QPalette::Button);
}

QPushButton* CFEffectWidget::setClearBtn() {
    QPushButton* btn = new QPushButton(tr("清除效果"));
    return btn;
}
