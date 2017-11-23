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

    table = new QTableWidget();
    table->setColumnCount(1);
    table->setRowCount(1);
    table->setRowHeight(0, 300);
    table->setColumnWidth(0, 300);

    table->setCellWidget(0, 0, cell);
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(table);


    this->setLayout(layout);
}
