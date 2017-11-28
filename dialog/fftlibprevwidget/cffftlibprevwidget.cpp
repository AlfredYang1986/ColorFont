#include "cffftlibprevwidget.h"

#include <QGridLayout>
#include "../importdialog/cfimportindexcell.h"
#include "../../common/pagewidget/PageWidget.h"

const int LIB_PAGE_COUNT = 48;

CFFFTLibPrevWidget::CFFFTLibPrevWidget(QWidget *parent)
    : QWidget(parent) {

    setupUi();
}

CFFFTLibPrevWidget::~CFFFTLibPrevWidget() {

}

void CFFFTLibPrevWidget::setupUi() {
    QVBoxLayout* layout = new QVBoxLayout();

    QGridLayout* table = new QGridLayout();

    int cols = 4;
    for (int index = 0; index <  LIB_PAGE_COUNT; ++index) {
//        CFImportIndexCell* cell = new CFImportIndexCell(pc, 34);
        QWidget* cell = new QWidget();
        int row = index / cols;
        int col = index % cols;
        table->addWidget(cell, row, col);
        cell->setObjectName(QString::number(index));
    }

    layout->addLayout(table);

    PageWidget* pw = new PageWidget();
    pw->setMaxPage(char_lst.size() / LIB_PAGE_COUNT + 1);
    pw->setCurrentPage(1);
    QString qss = QString(".QLabel[page=\"true\"] { padding: 1px; }")
            + QString(".QLabel[currentPage=\"true\"] { color: rgb(190, 0, 0);}")
            + QString(".QLabel[page=\"true\"]:hover { color: white; border-radius: 4px; background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(53, 121, 238, 255), stop:1 rgba(0, 202, 237, 255));}");
    pw->setStyleSheet(qss);
    QObject::connect(pw, SIGNAL(currentPageChanged(int)), this, SLOT(slot_pageChanged(int)));

    layout->addWidget(pw);
    layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));

    this->setLayout(layout);
}

void CFFFTLibPrevWidget::slot_pageChanged(int p) {

}
