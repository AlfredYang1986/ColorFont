#import "cfimportindexcell.h"

#include <QLineEdit>
#include <QVBoxLayout>
#include "../previewwidget/cfpreviewwidget.h"
#include "../../module/modulemanagement/cfmm.h"
#include <QAction>
#include <QMenu>

CFImportIndexCell::CFImportIndexCell(
        FT_Face p,
        FT_ULong ccd,
        QWidget *parent)
    : QWidget(parent), m(NULL), pc(p), charcode(ccd) {

    setupUi();

}

CFImportIndexCell::~CFImportIndexCell() {
    w->releaseResources();
// context 由QGLWidget自己释放
}

void CFImportIndexCell::setupUi() {

    QVBoxLayout* layout = new QVBoxLayout();

    QGLFormat qglFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
    qglFormat.setVersion(4, 2);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    qglFormat.setSampleBuffers(true);
    context = new QGLContext(qglFormat);

    w = new CFPreviewWidget(pc, charcode, context);
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(w);

//    QLineEdit* edit = new QLineEdit();
//    edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
//    layout->addWidget(edit);

    this->setLayout(layout);
}

QSize CFImportIndexCell::sizeHint() const {
    return QSize(100, 100);
}

void CFImportIndexCell::resetCharcode(FT_ULong code) {
    w->resetCharcode(code);
}

void CFImportIndexCell::repaintOpenGL() {
    w->repaintOpenGL();
}

void CFImportIndexCell::contextMenuEvent(QContextMenuEvent *) {

    if (m == NULL) {
        m = new QMenu(this);
        {
            QAction* action = new QAction(tr("导入字库"), this);
            QObject::connect(action, SIGNAL(triggered()), this, SLOT(slot_importCodeAsChar()));
            m->addAction(action);
        }
        {
            QAction* action = new QAction(tr("导入符号"), this);
            QObject::connect(action, SIGNAL(triggered()), this, SLOT(slot_importCodeAsSymbol()));
            m->addAction(action);
        }
    }

    m->move(cursor().pos());
    m->show();
}

void CFImportIndexCell::slot_importCodeAsChar() {
    qDebug() << "import charcode as char";

    CFModuleManagement* cfmm =
            CFModuleManagement::queryInstance();

    CFFuncArguments args;

    {
        QVariant v;
        v.setValue(pc);
        args.pushV("face", v);
    }

    {
        QVariant v;
        v.setValue(charcode);
        args.pushV("charcode", v);
    }

//    {
//        QVariant v;
//        v.setValue("");
//        args.pushV("index", v);
//    }

    cfmm->pushMessage(FFT_MODULE, FFT_IMPORT_CHAR, args);
}

void CFImportIndexCell::slot_importCodeAsSymbol() {
    qDebug() << "import charcode as symbol";

    CFModuleManagement* cfmm =
            CFModuleManagement::queryInstance();

    CFFuncArguments args;

    {
        QVariant v;
        v.setValue(pc);
        args.pushV("face", v);
    }

    {
        QVariant v;
        v.setValue(charcode);
        args.pushV("charcode", v);
    }

//    {
//        QVariant v;
//        v.setValue("");
//        args.pushV("index", v);
//    }

    cfmm->pushMessage(FFT_MODULE, FFT_IMPORT_SYMBOL, args);

}
