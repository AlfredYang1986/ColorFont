#include "cfprevdialog.h"
#include "ui_prevdialog.h"

#include <QStandardItem>
#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSplitterHandle>
#include <QSize>

#include <QDebug>

CFPrevDialog::CFPrevDialog(QWidget *parent)
//    : QDialog(parent), ui(new Ui::CFPrevDialog) {
    : QSplitter(Qt::Horizontal, parent) {

    setupUI();
}

void CFPrevDialog::setupUI() {
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::MSWindowsFixedSizeDialogHint);

    /**
     * left
     */
    QWidget* lv = new QWidget(this);
    QVBoxLayout* lvl = new QVBoxLayout();

    left = new QListView();
    setLeftListViewModel();

    lvl->addWidget(left);

    QPushButton* closeButton = new QPushButton();
    closeButton->setText("关闭");
    QObject::connect(closeButton, SIGNAL(pressed()), this, SLOT(closeButton_toggle()));
    lvl->addWidget(closeButton);

    lv->setLayout(lvl);
    this->addWidget(lv);

    /**
     * right
     */
    right = new QTableView();
    setRightListViewModel();
    this->addWidget(right);

    this->setStretchFactor(1, 3);
    this->resize(800, 600);

    this->setStyleSheet("QSplitter::handle { background-color: black }");
    QSplitterHandle *splitterHandle = this->handle(1);
    if (splitterHandle)
        splitterHandle->setDisabled(true);
}

void CFPrevDialog::setLeftListViewModel() {

    QStandardItemModel *qstmodel=new QStandardItemModel();
    QStandardItem* item1    = new QStandardItem("最近");
    QStandardItem* item2    = new QStandardItem("打开字体文件");

    qstmodel->appendRow(item1);
    qstmodel->appendRow(item2);

    QListView *view = left;
    view->setModel(qstmodel);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setAutoFillBackground(true);

    // TODO: 这里要变好看
}

void CFPrevDialog::setRightListViewModel() {

}

void CFPrevDialog::closeButton_toggle() {
    qDebug() << "close button toggle" ;
    this->close();
    exit(0);
}
