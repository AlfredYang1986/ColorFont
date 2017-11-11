#include "cfprevdialog.h"

#include <QStandardItem>
#include <QStandardItemModel>
#include <QListView>
#include <QTableView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSplitterHandle>
#include <QSize>

#include "../module/modulemanagement/cfmm.h"

#include <QDebug>

CFPrevDialog::CFPrevDialog(QWidget *parent)
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
    // TODO: 最近保存数据逻辑，现在是假的

    QStandardItemModel *qstmodel=new QStandardItemModel();
    QStandardItem* item1    = new QStandardItem("调用FileModule的Open函数");
    QStandardItem* item2    = new QStandardItem("调用FFTModule的Load函数");

    QList<QStandardItem*> l;
    l.append(item1);
    l.append(item2);
    qstmodel->insertRow(0, l);

    QTableView *view = right;
    view->setModel(qstmodel);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setAutoFillBackground(true);

    QObject::connect(view, SIGNAL(clicked(QModelIndex)),
                     this, SLOT(resent_file_clicked(QModelIndex)));

    // TODO: 这里要变好看
}

void CFPrevDialog::closeButton_toggle() {
    qDebug() << "close button toggle" ;
    this->close();
    exit(0);
}

void CFPrevDialog::resent_file_clicked(const QModelIndex & index) {
    qDebug() << index << "clicked";
    if (index.row() == 0 && index.column() == 0) {

        const CFModuleManagement* cffm = CFModuleManagement::queryInstance();
        const QMap<QString, QObject>* result =
            const_cast<CFModuleManagement*>(cffm)->pushMessage("file", "open", NULL);

        QMap<QString, QObject>::const_iterator iter = result->begin();
        while(iter != result->end()) {
            qDebug() << "result is :" << iter.key() << endl;
        }

    } else if (index.row() == 0 && index.column() == 0) {

    } else {
        // do nothing
    }
}
