#include "cfpreviewwidget.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <QtOpenGL/QtOpenGL>
#include <QOpenGLShaderProgram>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <QDebug>

static const char *vertexShaderSourceCore =
    "#version 410\n"
    "layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex> \n"
    "out vec2 TexCoords;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "	gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
    "	TexCoords = vertex.zw;\n"
    "}\n";

static const char *fragmentShaderSourceCore =
    "#version 410\n"
    "in vec2 TexCoords;\n"
    "out vec4 color;\n"
    "uniform sampler2D text;\n"
    "uniform vec3 textColor;\n"
    "void main() {\n"
    "	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
    "	color = vec4(textColor, 1.0) * sampled;\n"
    "}\n";

CFPreviewWidget::CFPreviewWidget(QGLContext *context, QWidget *parent)
    : QGLWidget(context, parent) {

    QGLFormat qglFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
    qglFormat.setVersion(4, 2);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    qglFormat.setSampleBuffers(true);

    setFormat(qglFormat);
}

CFPreviewWidget::~CFPreviewWidget() {

}

void CFPreviewWidget::initializeGL() {
    qDebug() << "OpenGL Versions Supported: " << QGLFormat::openGLVersionFlags() << "\n";
    printf("version: %s\n", (char*)glGetString(GL_VERSION));
    qglClearColor(Qt::black);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

    glShadeModel(GL_FLAT); 	// 设置阴影平滑模式
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    program = new QOpenGLShaderProgram;
    program->addShaderFromSourceCode(
                QOpenGLShader::Vertex, vertexShaderSourceCore);
    program->addShaderFromSourceCode(
                QOpenGLShader::Fragment, vertexShaderSourceCore);

    program->link();
    program->bind();

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    glUniformMatrix4fv(glGetUniformLocation(program->programId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

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
}

void CFPreviewWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    draw();
}

