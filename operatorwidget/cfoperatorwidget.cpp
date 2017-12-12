#include "cfoperatorwidget.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include "../operatorwidget/cfgllinewidget.h"

CFOperatorWidget::CFOperatorWidget(QWidget *parent)
    : QMdiSubWindow(parent) {

    this->resize(800, 400);
    setupUi();
}

CFOperatorWidget::~CFOperatorWidget() {

}

void CFOperatorWidget::setupUi() {

    QScrollArea* s = new QScrollArea();
    s->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    s->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QGLFormat qglFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
    qglFormat.setVersion(4, 2);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    qglFormat.setSampleBuffers(true);
    QGLContext* context = new QGLContext(qglFormat);

    QWidget* content = new QWidget();
    content->setMinimumSize(600, 500);
    {
        QVBoxLayout* col = new QVBoxLayout();

        col->addSpacerItem(new QSpacerItem(0, 50, QSizePolicy::Expanding, QSizePolicy::Fixed));

        QHBoxLayout* line = new QHBoxLayout();
        line->addSpacerItem(new QSpacerItem(50, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));

        CFGLLineWidget* w = new CFGLLineWidget(context);
        line->addWidget(w);

        line->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

        contents.append(w);

        col->addLayout(line);
        col->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

        content->setLayout(col);
    }

    s->setWidget(content);
    this->setWidget(s);
}

void CFOperatorWidget::pushCharacter(FT_Face face, FT_ULong charcode) {
    CFGLLineWidget* cur = contents.first();
    cur->pushCharacter(face, charcode);
    QSize s = cur->sizeHint();
    cur->resize(s);
    cur->resizeGL(s.width(), s.height());
    this->update();
}
