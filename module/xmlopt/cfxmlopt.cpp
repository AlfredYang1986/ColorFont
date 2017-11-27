#include "cfxmlopt.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QFile>

CFFuncResults
load_font_config(const CFFuncArguments& args);
CFFuncResults
push_font_node(const CFFuncArguments& args);
CFFuncResults
pop_font_node(const CFFuncArguments& args);
CFFuncResults
sync_doc(const CFFuncArguments& args);

static const QString config_path = "/ttf_config.conf";

CFXMLOpt::CFXMLOpt() : doc(NULL), file(NULL) {
    funcs = {
        std::make_pair(FFT_XML_LOAD, &load_font_config),
        std::make_pair(FFT_XML_PUSH, &push_font_node),
        std::make_pair(FFT_XML_POP, &pop_font_node),
        std::make_pair(FFT_XML_SYNC, &sync_doc)
    };
}

CFXMLOpt::~CFXMLOpt() {
    if (doc) {
        delete doc;
    }

    if (file) {
        if (file->isOpen()) {
            file->close();
        }
        delete file;
    }
}

bool CFXMLOpt::init_config() {
    const int Indent = 4;
    QString path = QCoreApplication::applicationDirPath() + config_path;
    bool result = false;
    file = new QFile(path);
    if (!file->exists()) {

        if(!file->open(QIODevice::WriteOnly)) {
            qDebug() << "Error: cannot create new file : " << path;
            result = false;
        } else {
            doc = new QDomDocument();
            QTextStream out(file);
            QDomNode xmlNode =
                    doc->createProcessingInstruction("xml",
                                                     "version=\"1.0\" encoding=\"ISO-8859-1\"");

            doc->insertBefore(xmlNode, doc->firstChild());

            QDomNode rootNode = doc->createElement("ttfs");
            doc->insertAfter(rootNode, xmlNode);

            doc->save(out, Indent);
            result = true;
        }
   } else {

        if (!file->open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug() << "Error: cannot open file : " << path;
            result = false;
        }

        QString errorStr;
        int errorLine;
        int errorColum;

        doc = new QDomDocument();
        if (!doc->setContent(file, false, &errorStr, &errorLine, &errorColum)) {
            qDebug() << "Error: Parse error at line " << errorLine << ", "
                     << "column " << errorColum << ": "
                     << errorStr;
            result = false;
        } else {
            result = true;
        }
    }

    return true;
}

CFFuncResults
load_font_config(const CFFuncArguments& args) {
    CFModuleManagement* cfmm =
            CFModuleManagement::queryInstance();
    CFXMLOpt* xml =
        (CFXMLOpt*)cfmm->queryModuleInstance(FFT_XML_MODULE);

    if (xml->doc == NULL) {
        xml->init_config();
    }

    return CFFuncResults();
}

CFFuncResults
push_font_node(const CFFuncArguments& args) {
    return CFFuncResults();
}

CFFuncResults
pop_font_node(const CFFuncArguments& args) {
    return CFFuncResults();
}

CFFuncResults
sync_doc(const CFFuncArguments& args) {

}

