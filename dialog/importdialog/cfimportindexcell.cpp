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

    CFModuleManagement* cfmm =
            CFModuleManagement::queryInstance();
    CFFuncResults result = cfmm->pushMessage(OPENGL_MODULE, QUERY_GL_CONTEXT, CFFuncArguments());
    QGLContext* context = result.getV("context").value<QGLContext*>();

    CFPreviewWidget* w = new CFPreviewWidget(pc, context);
//    QWidget* w = new QWidget();
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    w->setFixedSize(100, 100);
    layout->addWidget(w);

    QLineEdit* edit = new QLineEdit();
    edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(edit);

    this->setLayout(layout);
}

QSize CFImportIndexCell::sizeHint() const {
    return QSize(100, 100);
}
