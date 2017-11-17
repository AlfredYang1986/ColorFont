#include "cfimgwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>

#include <QDebug>

CFImgWidget::CFImgWidget(QWidget *parent)
    : QWidget(parent) {

    setupUi();
}

CFImgWidget::~CFImgWidget() {

}

void CFImgWidget::setupUi() {

    QVBoxLayout* layout = new QVBoxLayout();

    QPushButton* import_btn = new QPushButton();
    import_btn->setText(tr("导入图片"));
    import_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(import_btn);

    QHBoxLayout* mid_layout = new QHBoxLayout();
    QWidget* left = new QWidget();
    left->setStyleSheet("background : black");
    mid_layout->addWidget(left);

    QVBoxLayout* right = new QVBoxLayout();

    // 平铺
    QPushButton* push_btn = new QPushButton(tr("平铺"));
    right->addWidget(push_btn);

    // 拉伸
    QPushButton* pull_btn = new QPushButton(tr("拉伸"));
    right->addWidget(pull_btn);

    // 填充
    QPushButton* fill_btn = new QPushButton(tr("填充"));
    right->addWidget(fill_btn);

    mid_layout->addLayout(right);

    layout->addLayout(mid_layout);
    layout->addSpacerItem(
                new QSpacerItem(0, 0,
                                QSizePolicy::Fixed,
                                QSizePolicy::Expanding));

    this->setLayout(layout);
}
