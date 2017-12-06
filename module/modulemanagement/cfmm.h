#ifndef CFMM_H
#define CFMM_H

#include <QObject>
#include <QMap>
#include "../../common/funcargs/cfargs.h"

static const QString QUERY_MODULE = "query module";
static const QString QUERY_MAIN_WINDOW = "query main window";
static const QString QUERY_PUSH_MAIN_WINDOW = "push main window";

static const QString FFT_XML_MODULE = "fft xml module";
static const QString FFT_XML_LOAD = "fft load xml file";
static const QString FFT_XML_SYNC = "fft sync xml file";
static const QString FFT_XML_PUSH = "fft xml file push node";
static const QString FFT_XML_POP = "fft xml file pop node";
static const QString FFT_XML_QUERY = "fft xml query node";
static const QString FFT_XML_COUNT = "fft xml query node count";

static const QString FILE_MODULE = "file module";
static const QString FILE_TTF_DIR = "create ttf dir";
static const QString FILE_MOVE_TO_TTF_DIR = "move to ttf dir";

static const QString FFT_MODULE = "fft";
static const QString FFT_LOAD_FILE = "load";
static const QString FFT_FREE_FACE = "free ttf file";
static const QString FFT_IMPORT_CHAR = "import char";
static const QString FFT_IMPORT_SYMBOL = "import symbol";
static const QString FFT_IMPORT_CHAR_LST = "import chars list";
static const QString FFT_IMPORT_SYMBOL_LST = "import symbols list";

static const QString OPENGL_MODULE = "opengl";
static const QString INIT_GL = "Init GL";
//static const QString QUERY_GL_CONTEXT = "query gl context";
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
