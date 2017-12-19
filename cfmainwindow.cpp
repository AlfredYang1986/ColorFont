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

    area = new QMdiArea();
    area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setCentralWidget(area);

    this->setWindowTitle(tr("方仪设计工具"));
}

CFMainWindow::~CFMainWindow() {
    delete ui;
}

void CFMainWindow::setupEffectDock() {
    effect_dock = new CFEffectDock();
    this->addDockWidget(Qt::RightDockWidgetArea, effect_dock);
}

void CFMainWindow::setupResentSymbolDock() {
    char_dock = new CFResentCharDock();
    this->addDockWidget(Qt::LeftDockWidgetArea , char_dock);
}

void CFMainWindow::on_actionClose_triggered() {
    // TODO: close all
    qDebug() << "close application";
}

void CFMainWindow::on_actionSaveAs_triggered() {
    // TODO: save as current edit with dialog
}

void CFMainWindow::on_actionSave_triggered() {
    qDebug() << "save current edit";
    CFOperatorWidget* ow = (CFOperatorWidget*)area->currentSubWindow();
    if (ow != NULL) {
        ow->save();
    }
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
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Open TTF File"),
                                                     "", "", 0);

    if (!file_name.isEmpty()) {
        CFOperatorWidget* w = new CFOperatorWidget();
        w->setWindowTitle(tr("New Window"));
        area->addSubWindow(w);
        w->loadPath(file_name);
        w->show();
    }
}

void CFMainWindow::slot_pushCharacter(FT_Face face, FT_ULong charcode) {
    qDebug() << "push char : " << charcode;
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

void CFMainWindow::slot_changeTextColor(const QColor& color) {
    CFOperatorWidget* ow = (CFOperatorWidget*)area->currentSubWindow();
    if (ow != NULL) {
        qDebug() << "about to change the color"
                 << "red is : " << color.red()
                 << "green is : " << color.green()
                 << "blue is : " << color.blue();
    }
}

void CFMainWindow::on_actionBrandNew_triggered() {
    CFOperatorWidget* w = new CFOperatorWidget();
    w->setWindowTitle(tr("New Window"));
    area->addSubWindow(w);
    w->show();
}
