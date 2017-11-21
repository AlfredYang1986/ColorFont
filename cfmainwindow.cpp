#include "cfmainwindow.h"
#include "ui_cfmainwindow.h"
#include "dockwidget/cfeffectdock.h"
#include "dockwidget/cfresentchardock.h"
#include <QMdiArea>
#include "operatorwidget/cfoperatorwidget.h"
#include "operatorwidget/cfoperatortab.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include "common/funcargs/cfargs.h"
#include "module/modulemanagement/cfmm.h"
#include "dialog/importdialog/cfimportttfdialog.h"

#include <QDebug>

CFMainWindow::CFMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CFMainWindow) {

    ui->setupUi(this);
    effect_dock = new CFEffectDock();
    this->addDockWidget(Qt::RightDockWidgetArea, effect_dock);

    char_dock = new CFResentCharDock();
    this->addDockWidget(Qt::LeftDockWidgetArea , char_dock);

//    QWidget* view = new QWidget();
//    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    QVBoxLayout* layout = new QVBoxLayout();
//    layout->addWidget(new CFOperatorTab());

    area = new QMdiArea();
    area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setCentralWidget(area);
//    layout->addWidget(area);
//    view->setLayout(layout);

//    setCentralWidget(view);

    this->setWindowTitle(tr("方仪设计工具"));
}

CFMainWindow::~CFMainWindow() {
    delete ui;
}

//void CFMainWindow::on_actionOpenFont_triggered() {
//    // TODO: Open a ttf file, and load ttf to the main area
//    qDebug() << "open action triggered";

//    CFOperatorWidget* w = new CFOperatorWidget(area);
//    w->show();
//}

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

void CFMainWindow::on_actionImportTTF_triggered() {
    QString file_name =
            QFileDialog::getOpenFileName(
                this,
                tr("Open TTF File"),
                "",
                "",
                0);

    if (!file_name.isNull()) {
        CFFuncArguments args;
        args.pushV("path", QVariant(file_name));

        CFModuleManagement* cfmm =
            CFModuleManagement::queryInstance();

        CFFuncResults reVal =
            cfmm->pushMessage("fft", "load", args);

        if (reVal.isOk()) {
            // TODO: show import dialog


        } else {
            qDebug() << "load fft error"
                     << "error is "
                     << reVal.getLastError().error_code
                     << reVal.getLastError().error_message;
        }

    } else {
        // 用户取消，什么都不做
    }
}
