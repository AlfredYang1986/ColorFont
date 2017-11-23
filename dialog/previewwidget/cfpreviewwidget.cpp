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
        FT_Face p,
        QGLContext* context,
        QWidget* parent)

    : QGLWidget(context, parent), pc(p) {

}

CFPreviewWidget::~CFPreviewWidget() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &(character.TextureID));

    if (program)
        delete program;
}

void CFPreviewWidget::initializeGL() {
    qglClearColor(Qt::black);

    CFModuleManagement* cfmm =
        CFModuleManagement::queryInstance();

    CFFuncResults reVal =
        cfmm->pushMessage(OPENGL_MODULE, INIT_GL, CFFuncArguments());

    program = reVal.getV("program").value<QOpenGLShaderProgram*>();

    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CFPreviewWidget::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);

    {
        FT_Face face = pc;

        CFFuncArguments args;

        {
            QVariant v;
            v.setValue(face);
            args.pushV("face", v);
        }

        {
            QVariant v;
            v.setValue('f');
            args.pushV("char", v);
        }

        CFModuleManagement* cfmm =
            CFModuleManagement::queryInstance();

        CFFuncResults result =
            cfmm->pushMessage(OPENGL_MODULE, LOAD_FROM_GLYPH, args);

        character = result.getV("character").value<Character>();
    }
}

void CFPreviewWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw(character);
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


    CFModuleManagement* cfmm =
        CFModuleManagement::queryInstance();

    cfmm->pushMessage(OPENGL_MODULE, DRAW_GLYPH, args);
}

