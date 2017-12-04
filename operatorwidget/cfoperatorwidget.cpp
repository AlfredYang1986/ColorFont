#include "cfoperatorwidget.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../operatorwidget/cfgllinewidget.h"

CFOperatorWidget::CFOperatorWidget(QWidget *parent)
    : QMdiSubWindow(parent) {

    this->resize(800, 400);
}

CFOperatorWidget::~CFOperatorWidget() {

}

void CFOperatorWidget::setupUi() {
    QVBoxLayout* layout = new QVBoxLayout();

    {
        QHBoxLayout* line = new QHBoxLayout();

        QGLFormat qglFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
        qglFormat.setVersion(4, 2);
        qglFormat.setProfile(QGLFormat::CoreProfile);
        qglFormat.setSampleBuffers(true);
        QGLContext* context = new QGLContext(qglFormat);

        CFGLLineWidget* w = new CFGLLineWidget(context);
        line->addSpacerItem(new QSpacerItem(10, 0, QSizePolicy::Preferred, QSizePolicy::Preferred));
        line->addWidget(w);
        line->addSpacerItem(new QSpacerItem(10, 0, QSizePolicy::Preferred, QSizePolicy::Preferred));
        contents.append(w);

        layout->addLayout(line);
    }

    this->setLayout(layout);
}
