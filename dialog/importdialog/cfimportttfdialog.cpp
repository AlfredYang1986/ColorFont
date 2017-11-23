#include "cfimportttfdialog.h"

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include "cfimportindexcell.h"
#include "../../common/funcargs/cfargs.h"

CFImportTTFDialog::CFImportTTFDialog(
        FT_Face p,
        QWidget *parent)
    : QDialog(parent), pc(p) {

    setupUi();
}

CFImportTTFDialog::~CFImportTTFDialog() {

}

void CFImportTTFDialog::setupUi() {
    QVBoxLayout* layout = new QVBoxLayout();

    CFImportIndexCell* cell = new CFImportIndexCell(pc);
    CFImportIndexCell* cell1 = new CFImportIndexCell(pc);

    table = new QTableWidget();
    table->setColumnCount(2);
    table->setRowCount(2);
    table->setRowHeight(0, 100);
    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 100);

    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAutoFillBackground(false);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setVisible(false);

    table->setCellWidget(0, 0, cell);
    table->setCellWidget(0, 1, cell1);
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(table);

    this->setLayout(layout);
}
