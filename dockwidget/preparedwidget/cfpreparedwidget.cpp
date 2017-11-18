#include "cfpreparedwidget.h"
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

CFPreparedWidget::CFPreparedWidget(QWidget *parent)
    : CFEffectWidget(parent) {

}

CFPreparedWidget::~CFPreparedWidget() {

}

void CFPreparedWidget::setupContent() {
    table = new QTableView();

//    table->setModel(qstmodel);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAutoFillBackground(false);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setVisible(false);
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    table->setStyleSheet("QTableView { background-color: green }");

    tab->addTab(table, tr("效果"));
}

void CFPreparedWidget::setControlPanel() {
    QVBoxLayout* up = new QVBoxLayout();

    QPushButton* apply2file = new QPushButton(tr("应用到当前编辑文档"));
    QPushButton* apply2all = new QPushButton(tr("应当到所有打开文档"));

    up->addWidget(apply2file);
    up->addWidget(apply2all);

    panel->setLayout(up);
}
