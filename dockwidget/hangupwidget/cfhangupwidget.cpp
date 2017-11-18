#include "cfhangupwidget.h"

#include <QWidget>
#include <QTabWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>

CFHangupWidget::CFHangupWidget(QWidget *parent)
    : CFEffectWidget(parent) {

}

CFHangupWidget::~CFHangupWidget() {

}

void CFHangupWidget::setupContent() {
    QWidget* view = new QWidget();
    view->setMinimumSize(150, 100);

    QHBoxLayout* layout = new QHBoxLayout();

    pic_prev = new QLabel();
    pic_prev->setMinimumWidth(50);
    pic_prev->setMinimumHeight(50);
    pic_prev->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pic_prev->setStyleSheet("QWidget { background-color : red }");

    layout->addWidget(pic_prev);
    layout->addLayout(this->createRightInputPanel());
    view->setLayout(layout);

    tab->addTab(view, tr("挂件"));
//    view->setStyleSheet("QWidget { background-color : red }");
}

void CFHangupWidget::setControlPanel() {
    // 导入图片btn
    QPushButton* apply_btn = new QPushButton(tr("导入图片"));

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(apply_btn);

    panel->setLayout(layout);
}

QHBoxLayout*
CFHangupWidget::createInputProperty(const QString& des,
                                    QLineEdit** edit) {

    *edit = new QLineEdit();
    (*edit)->setMaximumWidth(30);

    QLabel* tmp = new QLabel(des);
    tmp->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    (*edit)->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    QHBoxLayout* tl = new QHBoxLayout();
    tl->addWidget(tmp);
    tl->addWidget(*edit);

    return tl;
}

QGridLayout*
CFHangupWidget::createRightInputPanel() {

    QGridLayout* tmp = new QGridLayout();

    tmp->addLayout(createInputProperty(tr("X"), &x), 0, 0);
    tmp->addLayout(createInputProperty(tr("Y"), &x), 0, 1);
    tmp->addLayout(createInputProperty(tr("W"), &x), 1, 0);
    tmp->addLayout(createInputProperty(tr("H"), &x), 1, 1);

    return tmp;
}
