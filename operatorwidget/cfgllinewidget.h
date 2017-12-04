#ifndef CFGLLINEWIDGET_H
#define CFGLLINEWIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <glm/glm.hpp>
#include "../common/funcargs/cfargs.h"
#include <QGLWidget>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class CFGLLineWidget : public QGLWidget {

    Q_OBJECT

public:
    explicit CFGLLineWidget(QGLContext* context,
                            QWidget* parent = 0);
    ~CFGLLineWidget();

    void repaintOpenGL();
    void releaseResources();
    void pushCharacter(FT_Face face, FT_ULong charcode);
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void paintEvent(QPaintEvent*);

private:
    void drawBackground();
    void draw(Character ch);
    void draw(const QVector<Character>& vec);

private:
    GLuint VAO, VBO, VAO_BK, VBO_BK;
    QOpenGLShaderProgram * program;
    QOpenGLShaderProgram * program_bk;
    QVector<Character> chars;
};

#endif // CFGLLINEWIDGET_H
