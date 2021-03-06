#include "cfpreviewwidget.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <QtOpenGL/QtOpenGL>
#include <QOpenGLShaderProgram>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../../common/funcargs/cfargs.h"
#include "../../module/modulemanagement/cfmm.h"
#include "../../module/openglopt/cfopenglopt.h"
#include <QDebug>


CFPreviewWidget::CFPreviewWidget(
        QGLContext* context,
        QWidget* parent)

    : QGLWidget(context, parent), pc(NULL), charcode(0) {

}

CFPreviewWidget::CFPreviewWidget(
        FT_Face p,
        FT_ULong ccd,
        QGLContext* context,
        QWidget* parent)

    : QGLWidget(context, parent), pc(p), charcode(ccd) {

}

void CFPreviewWidget::releaseResources() {
    makeCurrent();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO_BK);
    glDeleteBuffers(1, &VBO_BK);
    glDeleteTextures(1, &(character.TextureID));

    if (program)
        delete program;

    if (program_bk)
        delete program_bk;

}

CFPreviewWidget::~CFPreviewWidget() {

}

void CFPreviewWidget::initializeGL() {
    makeCurrent();
    qglClearColor(Qt::black);

    CFModuleManagement* cfmm =
        CFModuleManagement::queryInstance();

    CFFuncResults reVal =
        cfmm->pushMessage(OPENGL_MODULE, INIT_GL, CFFuncArguments());

    program = reVal.getV("program").value<QOpenGLShaderProgram*>();
    program_bk = reVal.getV("program_bk").value<QOpenGLShaderProgram*>();

    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &VAO_BK);
    glGenBuffers(1, &VBO_BK);
    glBindVertexArray(VAO_BK);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_BK);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 2, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    if (pc)
        this->resetCharcode(charcode);
}

void CFPreviewWidget::resizeGL(int width, int height) {
    makeCurrent();
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}

void CFPreviewWidget::paintGL() {
    makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (pc && charcode > 0) {
        draw(character);
    }
//    drawBackground();
}

void CFPreviewWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    /**
     * background
     */
    p.fillRect(this->rect(), Qt::white);

    /**
     * border
     */
//    p.drawRoundedRect(this->rect(), 5, 5);
    paintGL();
}

void CFPreviewWidget::drawBackground() {
    CFFuncArguments args;

    {
        QVariant v;
        v.setValue(VAO_BK);
        args.pushV("VAO", v);
    }

    {
        QVariant v;
        v.setValue(VBO_BK);
        args.pushV("VBO", v);
    }

    {
        QVariant v;
        v.setValue(program_bk);
        args.pushV("program", v);
    }

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    cfmm->pushMessage(OPENGL_MODULE, DRAW_BACKGROUND, args);
}

void CFPreviewWidget::draw(Character ch) {

    CFFuncArguments args;

    {
        QVariant v;
        v.setValue(VAO);
        args.pushV("VAO", v);
    }

    {
        QVariant v;
        v.setValue(VBO);
        args.pushV("VBO", v);
    }

    {
        QVariant v;
        v.setValue(ch);
        args.pushV("character", v);
    }

    {
        QVariant v;
        v.setValue(program);
        args.pushV("program", v);
    }

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    cfmm->pushMessage(OPENGL_MODULE, DRAW_GLYPH, args);
}

void CFPreviewWidget::resetFace(FT_Face face) {
    pc = face;
}

void CFPreviewWidget::resetCharcode(FT_ULong code) {
    makeCurrent();
    charcode = code;
    if (pc != NULL)  {
        FT_Face face = pc;

        CFFuncArguments args;

        {
            QVariant v;
            v.setValue(face);
            args.pushV("face", v);
        }

        {
            QVariant v;
            v.setValue(charcode);
            args.pushV("charcode", v);
        }

        CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
        CFFuncResults result = cfmm->pushMessage(OPENGL_MODULE, LOAD_FROM_GLYPH, args);
        character = result.getV("character").value<Character>();
//        QString name = result.getV("name").value<QString>();
//        qDebug() << "charcode name is " << name;
    }
}

void CFPreviewWidget::repaintOpenGL() {
//    this->updateGL();
    this->update();
}
