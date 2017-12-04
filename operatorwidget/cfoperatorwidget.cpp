#include "cfoperatorwidget.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../operatorwidget/cfgllinewidget.h"

CFOperatorWidget::CFOperatorWidget(QWidget *parent)
    : QMdiSubWindow(parent) {

    this->resize(800, 400);
    setupUi();
}

CFOperatorWidget::~CFOperatorWidget() {

}

void CFOperatorWidget::setupUi() {

    QWidget* w = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();

    {
        QGLFormat qglFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
        qglFormat.setVersion(4, 2);
        qglFormat.setProfile(QGLFormat::CoreProfile);
        qglFormat.setSampleBuffers(true);
        QGLContext* context = new QGLContext(qglFormat);

        QHBoxLayout* line = new QHBoxLayout();
        CFGLLineWidget* w = new CFGLLineWidget(context);
        w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        line->addSpacerItem(new QSpacerItem(10, 0, QSizePolicy::Preferred, QSizePolicy::Preferred));
        line->addWidget(w);
        line->addSpacerItem(new QSpacerItem(10, 0, QSizePolicy::Preferred, QSizePolicy::Preferred));
        contents.append(w);

        layout->addLayout(line);
    }

    w->setLayout(layout);
//    this->setLayout(layout);
    this->setWidget(w);
}

void CFOperatorWidget::pushCharacter(FT_Face face, FT_ULong charcode) {
    contents.first()->pushCharacter(face, charcode);
}
