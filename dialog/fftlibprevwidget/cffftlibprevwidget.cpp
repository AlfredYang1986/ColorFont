#include "cffftlibprevwidget.h"

#include <QGridLayout>
#include "../importdialog/cfimportindexcell.h"
#include "../previewwidget/cfpreviewwidget.h"
#include "../../common/pagewidget/PageWidget.h"
#include "../../module/modulemanagement/cfmm.h"
#include "../../common/funcargs/cfargs.h"
#include "../../cfmainwindow.h"

const int LIB_PAGE_COUNT = 48;

CFFFTLibPrevWidget::CFFFTLibPrevWidget(QWidget *parent)
    : QWidget(parent), cur_lst(NULL), _is_connected(false) {

    setupUi();
}

CFFFTLibPrevWidget::~CFFFTLibPrevWidget() {

}

void CFFFTLibPrevWidget::setupUi() {
    QVBoxLayout* layout = new QVBoxLayout();

    QGridLayout* table = new QGridLayout();

    int cols = 4;
    for (int index = 0; index < LIB_PAGE_COUNT; ++index) {
        CFImportIndexCell* cell = new CFImportIndexCell();
        cell->setMinimumSize(50, 50);

        int row = index / cols;
        int col = index % cols;
        table->addWidget(cell, row, col);
        cell->setObjectName(QString::number(index));
    }

    layout->addLayout(table);

    PageWidget* pw = new PageWidget();
//    pw->setMaxPage(char_lst.size() / LIB_PAGE_COUNT + 1);
    pw->setMaxPage(1);
    pw->setCurrentPage(1);
    QString qss = QString(".QLabel[page=\"true\"] { padding: 1px; }")
            + QString(".QLabel[currentPage=\"true\"] { color: rgb(190, 0, 0);}")
            + QString(".QLabel[page=\"true\"]:hover { color: white; border-radius: 4px; background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(53, 121, 238, 255), stop:1 rgba(0, 202, 237, 255));}");
    pw->setStyleSheet(qss);
    QObject::connect(pw, SIGNAL(currentPageChanged(int)), this, SLOT(slot_pageChanged(int)));

    layout->addWidget(pw);
    layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));

    this->setLayout(layout);

    slot_pageChanged(1);
}

void CFFFTLibPrevWidget::slot_pageChanged(int p) {
    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();

    QVariant v;
    v.setValue(p - 1);
    CFFuncArguments args;
    args.pushV("page", v);

    CFFuncResults result =
        cfmm->pushMessage(FFT_XML_MODULE, FFT_XML_QUERY, args);

    if (cur_lst)
        delete cur_lst;

    cur_lst = result.getV("lst").value<QList<exchange_type>*>();
    static const QString config_path = QCoreApplication::applicationDirPath() + "/ttf_dir/";

    for (int index = 0; index < cur_lst->size(); ++index) {
        QString file_name = config_path + cur_lst->at(index).path;

        FT_Face face;
        {
            CFFuncArguments args;
            args.pushV("path", QVariant(file_name));
            CFFuncResults result = cfmm->pushMessage(FFT_MODULE, FFT_LOAD_FILE, args);
            face = result.getV("face").value<FT_Face>();
        }

        {
            CFImportIndexCell* cell = this->findChild<CFImportIndexCell*>(QString::number(index));
            FT_ULong ccd = cur_lst->at(index).charcode;
            cell->resetFace(face);
            cell->resetCharcode(ccd);
            cell->repaintOpenGL();
        }
    }
}

void CFFFTLibPrevWidget::showEvent(QShowEvent * ) {

    if (!_is_connected) {
        CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
        CFFuncResults reVal = cfmm->pushMessage(QUERY_MODULE, QUERY_MAIN_WINDOW, CFFuncArguments());
        CFMainWindow* w = reVal.getV("main_window").value<CFMainWindow*>();

        for (int index = 0; index < cur_lst->size(); ++index) {
            CFImportIndexCell* cell = this->findChild<CFImportIndexCell*>(QString::number(index));
            QObject::connect(cell, SIGNAL(signal_pressed(FT_Face, FT_ULong)),
                             w, SLOT(slot_pushCharacter(FT_Face, FT_ULong)));
        }

        _is_connected = true;
    }
}
