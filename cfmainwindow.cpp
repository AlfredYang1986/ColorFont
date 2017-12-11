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
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Open TTF File"),
                                                     "", "", 0);

    if (!file_name.isNull()) {
        CFFuncArguments args;
        args.pushV("path", QVariant(file_name));

        CFModuleManagement* cfmm = CFModuleManagement::queryInstance();

        CFFuncResults reVal =
            cfmm->pushMessage(FFT_MODULE, FFT_LOAD_FILE, args);

        if (reVal.isOk()) {
            FT_Face c = reVal.getV("face").value<FT_Face>();
            CFImportTTFDialog dialog(c, this);
            dialog.resize(600, 300);
            dialog.exec();
            qDebug() << "close dialog";

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

void CFMainWindow::on_actionOpen_triggered() {
    CFOperatorWidget* w = new CFOperatorWidget();
    w->setWindowTitle(tr("New Window"));
    area->addSubWindow(w);
    w->show();
}

void CFMainWindow::slot_pushCharacter(FT_Face face, FT_ULong charcode) {
    qDebug() << "wo kao push char : " << charcode;
    CFOperatorWidget* ow = (CFOperatorWidget*)area->currentSubWindow();
    if (ow != NULL) {
        ow->pushCharacter(face, charcode);
    }
}

void CFMainWindow::slot_refreshCharacters() {
    qDebug() << "import characters need refresh";
}

void CFMainWindow::slot_resentDockPanelClosed() {
    qDebug() << "resent dock panel closed";
    if (char_dock) {
        char_dock->deleteLater();
    }
}

void CFMainWindow::slot_controlPanelClosed() {
    qDebug() << "resent dock panel closed";
    if (effect_dock) {
        effect_dock->deleteLater();
    }
}
