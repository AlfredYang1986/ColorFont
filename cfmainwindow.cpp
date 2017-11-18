#include "cfmainwindow.h"
#include "ui_cfmainwindow.h"
#include "dockwidget/cfeffectdock.h"
#include "dockwidget/cfresentchardock.h"
#include <QMdiArea>
#include "operatorwidget/cfoperatorwidget.h"

#include <QDebug>

CFMainWindow::CFMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CFMainWindow) {

    ui->setupUi(this);
    effect_dock = new CFEffectDock();
    this->addDockWidget(Qt::RightDockWidgetArea, effect_dock);

    char_dock = new CFResentCharDock();
    this->addDockWidget(Qt::LeftDockWidgetArea , char_dock);

    area = new QMdiArea();
    setCentralWidget(area);

    this->setWindowTitle(tr("方仪设计工具"));
}

CFMainWindow::~CFMainWindow() {
    delete ui;
}

void CFMainWindow::on_actionOpenFont_triggered() {
    // TODO: Open a ttf file, and load ttf to the main area
    qDebug() << "open action triggered";

    CFOperatorWidget* w = new CFOperatorWidget(area);
    w->show();
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
