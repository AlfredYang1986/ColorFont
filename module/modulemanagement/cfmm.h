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
static const QString FFT_XML_PUSH_TIMES = "fft xml push times";

static const QString FFT_XML_SAVE_CURRENT = "fft xml save current";
static const QString FFT_XML_SAVE_CURRENT_PRO = "fft xml save current profile";
static const QString FFT_XML_SAVE_TTF_FILES = "fft xml save current resources files";

static const QString FFT_XML_LOAD_CURRENT = "fft xml load current";
static const QString FFT_XML_LOAD_CURRENT_PRO = "fft xml load current profile";
static const QString FFT_XML_LOAD_TTF_FILES = "fft xml load current resources files";

static const QString FILE_MODULE = "file module";
static const QString FILE_TTF_DIR = "create ttf dir";
static const QString FILE_MOVE_TO_TTF_DIR = "move to ttf dir";
static const QString FILE_SAVE_DIR = "carete save dir";
static const QString FILE_CHECK_SAVE_DIR = "check save dir";

static const QString FFT_MODULE = "fft";
static const QString FFT_LOAD_FILE = "load";
static const QString FFT_FREE_FACE = "free ttf file";
static const QString FFT_IMPORT_CHAR = "import char";
static const QString FFT_IMPORT_SYMBOL = "import symbol";
static const QString FFT_IMPORT_CHAR_LST = "import chars list";
static const QString FFT_IMPORT_SYMBOL_LST = "import symbols list";
static const QString FFT_QUERY_PATHS_FROM_FACES = "query paths from faces";
static const QString FFT_QUERY_PATH_BY_FACE = "query path by face";

static const QString OPENGL_MODULE = "opengl";
static const QString INIT_GL = "Init GL";
//static const QString QUERY_GL_CONTEXT = "query gl context";
static const QString RELEASE_TEXTURE = "release texture";
static const QString LOAD_FROM_GLYPH = "load from glyph";
static const QString DRAW_GLYPH = "draw glyph";
static const QString DRAW_BACKGROUND = "draw background";
static const QString DRAW_GLYPH_LST = "draw glyph list";

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
