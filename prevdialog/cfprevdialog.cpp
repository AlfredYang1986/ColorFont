#include "cfprevdialog.h"
#include "ui_prevdialog.h"

CFPrevDialog::CFPrevDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::CFPrevDialog) {

    ui->setupUi(this);
}
