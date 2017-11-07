#include "cfmainwindow.h"
#include "ui_cfmainwindow.h"

#include <QDebug>

CFMainWindow::CFMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CFMainWindow) {

    ui->setupUi(this);
}

CFMainWindow::~CFMainWindow() {
    delete ui;
}

void CFMainWindow::on_actionOpenFont_triggered() {
    // TODO: Open a ttf file, and load ttf to the main area
    qDebug() << "open action triggered";

}

void CFMainWindow::on_actionClose_triggered() {
    // TODO: close all
    qDebug() << "close application";
}

void CFMainWindow::on_actionSaveAs_triggered() {
    // TODO: save as current edit with dialog
}

void CFMainWindow::on_actionSave_triggered() {
    // TODO: save current edit
}
