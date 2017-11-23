#import "cfimportindexcell.h"

#include <QLineEdit>
#include <QVBoxLayout>
#include "../previewwidget/cfpreviewwidget.h"
#include "../../module/modulemanagement/cfmm.h"

CFImportIndexCell::CFImportIndexCell(
        FT_Face p,
        QWidget *parent)
    : QWidget(parent), pc(p) {

    setupUi();
}

CFImportIndexCell::~CFImportIndexCell() {

}

void CFImportIndexCell::setupUi() {

    QVBoxLayout* layout = new QVBoxLayout();

//    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
//    CFFuncResults result = cfmm->pushMessage(OPENGL_MODULE, QUERY_GL_CONTEXT, CFFuncArguments());
//    QGLContext* context = result.getV("context").value<QGLContext*>();

    QGLFormat qglFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
    qglFormat.setVersion(4, 2);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    qglFormat.setSampleBuffers(true);
    QGLContext* context = new QGLContext(qglFormat);

    CFPreviewWidget* w = new CFPreviewWidget(pc, context);
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(w);

    QLineEdit* edit = new QLineEdit();
    edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(edit);

    this->setLayout(layout);
}

QSize CFImportIndexCell::sizeHint() const {
    return QSize(100, 100);
}
