#ifndef CFMM_H
#define CFMM_H

#include <QObject>
#include <QMap>
#include "../../common/funcargs/cfargs.h"

static const QString FFT_MODULE = "fft";
static const QString FFT_LOAD_FILE = "load";
static const QString FFT_IMPORT_CHAR = "import char";
static const QString FFT_IMPORT_SYMBOL = "import symbol";

static const QString OPENGL_MODULE = "opengl";
static const QString INIT_GL = "Init GL";
static const QString QUERY_GL_CONTEXT = "query gl context";
static const QString RELEASE_TEXTURE = "release texture";
static const QString LOAD_FROM_GLYPH = "load from glyph";
static const QString DRAW_GLYPH = "draw glyph";
static const QString DRAW_BACKGROUND = "draw background";

class CFBaseModule;

class CFModuleManagement : public QObject {

    Q_OBJECT

protected:
    explicit CFModuleManagement();

public:
    static CFModuleManagement* queryInstance();
    ~CFModuleManagement();

public:
    void initCFModules();
    void destoryCFModules();

    CFBaseModule* queryModuleInstance(const QString& module) const;

    CFFuncResults
    pushMessage(const QString& module,
                const QString& method,
                const CFFuncArguments& args);

private:
    static CFModuleManagement* instance;

    QList<std::pair<QString, CFBaseModule*> > mms;
};

#endif // CFMM_H
