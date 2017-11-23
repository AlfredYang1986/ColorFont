#ifndef CFOPENGLOPT_H
#define CFOPENGLOPT_H

#include <QtOpenGL/QtOpenGL>
#include <QOpenGLShaderProgram>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../basemodules/cfbasemodule.h"

class CFModuleManagement;

class CFOpenGLOpt : public CFBaseModule {

    Q_OBJECT
protected:
    explicit CFOpenGLOpt();

public:
    ~CFOpenGLOpt();

    bool hasInit() const;
    void inited();
    QGLContext* systemGLContext() const;

    QOpenGLShaderProgram* program;
private:
    bool _is_init;
    QGLContext* context;

    friend class CFModuleManagement;
};

#endif // CFOPENGLOPT_H
