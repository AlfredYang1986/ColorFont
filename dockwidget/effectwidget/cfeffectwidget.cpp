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

    this->setStyleSheet(
                "QTabWidget::pane {/* The tab widget frame */"
                    "border-top:2px solid #C2C7CB;"
                "}"
                "QTabWidget::tab-bar {"
                    "left:5px;/* move to the right by 5px */"
                "}"
                "QTabBar::tab {"
                    "background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                        "stop:0#E1E1E1, stop: 0.4 #DDDDDD,"
                        "stop:0.5#D8D8D8, stop: 1.0 #D3D3D3);"
                        "border:2px solid #C4C4C3;"
                        "border-bottom-color:#C2C7CB; /* same as the pane color */"
                        "border-top-left-radius:4px;"
                        "border-top-right-radius:4px;"
                        "min-width:8ex;"
                        "padding:2px;"
                    "}"
                "QTabBar::tab:selected,QTabBar::tab:hover {"
                    "background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                        "stop:0#fafafa, stop: 0.4 #f4f4f4,"
                        "stop:0.5#e7e7e7, stop: 1.0 #fafafa);"
                    "}"
                "QTabBar::tab:selected {"
                    "border-color:#9B9B9B;"
                    "border-bottom-color:#C2C7CB; /* same as pane color */"
                "}"
                "QTabBar::tab:!selected {"
                    "margin-top:2px;/* make non-selected tabs look smaller */"
                "}"
    );


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

void CFEffectWidget::slot_effectColorChange(const QColor &) {

}
