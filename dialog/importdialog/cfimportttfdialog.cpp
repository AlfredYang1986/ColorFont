#include "cfimportttfdialog.h"

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include "cfmainwindow.h"
#include "cfimportindexcell.h"
#include "../../common/funcargs/cfargs.h"
#include "../../common/pagewidget/PageWidget.h"
#include "../../module/modulemanagement/cfmm.h"

const int PAGE_COUNT = 27;
//const int PAGE_COUNT = 1;

CFImportTTFDialog::CFImportTTFDialog(
        FT_Face p,
        QWidget *parent)
    : QDialog(parent), pc(p) {

    setupUi();
}

CFImportTTFDialog::~CFImportTTFDialog() {
    CFFuncArguments args;
    QVariant v;
    v.setValue(pc);
    args.pushV("face", v);
    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    cfmm->pushMessage(FFT_MODULE, FFT_FREE_FACE, args);
}

void CFImportTTFDialog::setupUi() {
    QVBoxLayout* layout = new QVBoxLayout();

    FT_Face face = pc;
    FT_ULong charcode;
    FT_UInt gindex;

    FT_Select_Charmap(face, FT_ENCODING_UNICODE);

    charcode = FT_Get_First_Char(face, &gindex);
    while (gindex != 0) {
        if (!FT_Load_Glyph(face, charcode, FT_LOAD_RENDER)) {
            char_lst.push_back(charcode);
        }
        charcode = FT_Get_Next_Char(face, charcode, &gindex);
    }

    qDebug() << "symbol count : " << char_lst.size();

    QGridLayout* table = new QGridLayout();

    int cols = 9;
    for (int index = 0; index < PAGE_COUNT; /*char_lst.size();*/ ++index) {
        CFImportIndexCell* cell = new CFImportIndexCell(pc, char_lst[index]);
        int row = index / cols;
        int col = index % cols;
        table->addWidget(cell, row, col);
        cell->setObjectName(QString::number(index));
    }

    layout->addLayout(table);

    PageWidget* pw = new PageWidget();
    pw->setMaxPage(char_lst.size() / PAGE_COUNT + 1);
    pw->setCurrentPage(1);
    QString qss = QString(".QLabel[page=\"true\"] { padding: 1px; }")
            + QString(".QLabel[currentPage=\"true\"] { color: rgb(190, 0, 0);}")
            + QString(".QLabel[page=\"true\"]:hover { color: white; border-radius: 4px; background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(53, 121, 238, 255), stop:1 rgba(0, 202, 237, 255));}");
    pw->setStyleSheet(qss);
    QObject::connect(pw, SIGNAL(currentPageChanged(int)), this, SLOT(slot_pageChanged(int)));

    layout->addWidget(pw);

    QHBoxLayout* control_panel = new QHBoxLayout();
    control_panel->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    QPushButton* import_btn = new QPushButton(tr("当作字符导入全部"));
    QObject::connect(import_btn, SIGNAL(released()), this, SLOT(slot_importCurrentFont()));
    control_panel->addWidget(import_btn);
    QPushButton* symbol_btn = new QPushButton(tr("当作符号导入全部"));
    QObject::connect(symbol_btn, SIGNAL(released()), this, SLOT(slot_importCurrentFont()));
    control_panel->addWidget(symbol_btn);
    control_panel->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    layout->addLayout(control_panel);

    this->setLayout(layout);

    {
        CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
        CFFuncResults reVal = cfmm->pushMessage(QUERY_MODULE, QUERY_MAIN_WINDOW, CFFuncArguments());
        CFMainWindow* w = reVal.getV("main_window").value<CFMainWindow*>();

        QObject::connect(this, SIGNAL(signal_importSuccess()),
                         w, SLOT(slot_refreshCharacters()));
    }
}

void CFImportTTFDialog::slot_pageChanged(int p) {
    for (int index = 0; index < PAGE_COUNT; ++index) {

        CFImportIndexCell* cell = this->findChild<CFImportIndexCell*>(QString::number(index));
        FT_ULong ccd = 0;
        if (index + PAGE_COUNT * (p - 1) < char_lst.size()) {
            ccd = char_lst[index + PAGE_COUNT * (p - 1)];
        }
        cell->resetCharcode(ccd);
        cell->repaintOpenGL();
    }
}

void CFImportTTFDialog::slot_importCurrentFont() {
    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();

    CFFuncArguments args;

    {
        QVariant v;
        v.setValue(pc);
        args.pushV("face", v);
    }

    {
        QVariant v;
        v.setValue(this->char_lst);
        args.pushV("char-lst", v);
    }

    cfmm->pushMessage(FFT_MODULE, FFT_IMPORT_CHAR_LST, args);

    if (QMessageBox::warning(this, tr("导入字符成功"), tr("导入字符成功"))
            == QMessageBox::Ok) {

        this->close();
    }
}

void CFImportTTFDialog::slot_importCurrentSymbol() {
    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();

    CFFuncArguments args;

    {
        QVariant v;
        v.setValue(pc);
        args.pushV("face", v);
    }

    {

        QVariant v;
        v.setValue(this->char_lst);
        args.pushV("char-lst", v);
    }

    cfmm->pushMessage(FFT_MODULE, FFT_IMPORT_SYMBOL_LST, args);

    if (QMessageBox::warning(this, tr("导入字符成功"), tr("导入字符成功"))
            == QMessageBox::Ok) {

        this->close();
    }
}

void CFImportTTFDialog::closeEvent(QCloseEvent *) {
    qDebug() << "about to close preview dialog";
    emit signal_importSuccess();
}
