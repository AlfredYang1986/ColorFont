#include "cfoperatorwidget.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QSet>
#include <QVector>
#include <QFileDialog>
#include "../operatorwidget/cfgllinewidget.h"
#include "../module/modulemanagement/cfmm.h"

CFOperatorWidget::CFOperatorWidget(QWidget *parent)
    : QMdiSubWindow(parent), file_path("") {

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
    storage.push_back(std::make_pair(face, charcode));
    CFGLLineWidget* cur = contents.first();
    cur->pushCharacter(face, charcode);
    QSize s = cur->sizeHint();
    cur->resize(s);
    cur->resizeGL(s.width(), s.height());
    this->update();
}

void CFOperatorWidget::save() {

    if (file_path.isEmpty()) {
        file_path = QFileDialog::getSaveFileName(this,
                                                 tr("Save File"),
                                                 "", "", 0);

        qDebug() << "file path is : " << file_path;
    }

    if (file_path.isEmpty())
        return ;

    QSet<FT_Face> faces;
    QVector<FT_ULong> chars;
    for (int index = 0; index < storage.size(); ++index) {
        std::pair<FT_Face, FT_ULong> tmp = storage[index];
        faces.insert(tmp.first);
//        chars.push_back(tmp.second);
    }

    CFFuncArguments args;
    {
        QVariant v;
        v.setValue(faces.toList().toVector());
        args.pushV("faces", v);
    }

    {
        QVariant v;
        v.setValue(storage);
        args.pushV("chars", v);
    }

    {
        QVariant v;
        v.setValue(file_path);
        args.pushV("save_path", v);
    }

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    cfmm->pushMessage(FFT_XML_MODULE, FFT_XML_SAVE_CURRENT, args);
}

void CFOperatorWidget::saveAs(const QString& path) {

    QString file_path = "";
    if (file_path.isEmpty()) {
        file_path = QFileDialog::getSaveFileName(this,
                                                 tr("Save File"),
                                                 "", "", 0);

        qDebug() << "file path is : " << file_path;
    }

    if (file_path.isEmpty())
        return ;

    QSet<FT_Face> faces;
    QVector<FT_ULong> chars;
    for (int index = 0; index < storage.size(); ++index) {
        std::pair<FT_Face, FT_ULong> tmp = storage[index];
        faces.insert(tmp.first);
//        chars.push_back(tmp.second);
    }

    CFFuncArguments args;
    {
        QVariant v;
        v.setValue(faces.toList().toVector());
        args.pushV("faces", v);
    }

    {
        QVariant v;
        v.setValue(storage);
        args.pushV("chars", v);
    }

    {
        QVariant v;
        v.setValue(file_path);
        args.pushV("save_path", v);
    }

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    cfmm->pushMessage(FFT_XML_MODULE, FFT_XML_SAVE_CURRENT, args);
}

void CFOperatorWidget::loadPath(const QString &path) {
    CFFuncArguments args;
    QVariant v;
    v.setValue(path);
    args.pushV("path", v);

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFFuncResults reVal = cfmm->pushMessage(FFT_XML_MODULE, FFT_XML_LOAD_CURRENT, args);
    storage = reVal.getV("chars").value<QVector<std::pair<FT_Face, FT_ULong> > >();

    CFGLLineWidget* cur = contents.first();

    for (int index = 0; index < storage.size(); ++index) {
        FT_Face face = storage[index].first;
        FT_ULong charcode = storage[index].second;
        cur->pushCharacter(face, charcode);
    }

    QSize s = cur->sizeHint();
    cur->resize(s);
    cur->resizeGL(s.width(), s.height());

    this->update();
}

void CFOperatorWidget::setCurrentFillColor(const QColor &color) {
    this->fill_color = color;
}

void CFOperatorWidget::setFillColor(const QColor& c) {
    CFGLLineWidget* cur = contents.first();
    cur->setFillColor(c);;
    cur->update();
}

void CFOperatorWidget::setBKGColor(const QColor& c) {
    CFGLLineWidget* cur = contents.first();
    cur->setBKGColor(c);
    cur->update();
}
