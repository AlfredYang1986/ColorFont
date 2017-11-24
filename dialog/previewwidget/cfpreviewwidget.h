#ifndef CFPREVIEWWIDGET_H
#define CFPREVIEWWIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <glm/glm.hpp>
#include "../../common/funcargs/cfargs.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class CFPreviewWidget : public QGLWidget {

    Q_OBJECT

public:
    explicit CFPreviewWidget(FT_Face pc,
                             FT_ULong ccd,
                             QGLContext* context,
                             QWidget* parent = 0);
    ~CFPreviewWidget();

    void resetCharcode(FT_ULong code);
    void repaintOpenGL();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    void draw(Character ch);

private:
    GLuint VAO, VBO;
    QOpenGLShaderProgram * program;
    Character character;
    FT_Face pc;
    FT_ULong charcode;
};

#endif // CFPREVIEWWIDGET_H
