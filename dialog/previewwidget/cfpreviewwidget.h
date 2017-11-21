#ifndef CFPREVIEWWIDGET_H
#define CFPREVIEWWIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <glm/glm.hpp>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class CFPreviewWidget : public QGLWidget {

    Q_OBJECT

public:
    explicit CFPreviewWidget(QGLContext* context,
                             QWidget* parent);
    ~CFPreviewWidget();

//    void

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    void draw();

private:
    QOpenGLShaderProgram* program;
    GLuint VAO, VBO;
};

#endif // CFPREVIEWWIDGET_H
