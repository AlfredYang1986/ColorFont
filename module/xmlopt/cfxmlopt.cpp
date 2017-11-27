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

CFXMLOpt::CFXMLOpt() : doc(NULL) {
    funcs = {
        std::make_pair(FFT_XML_LOAD, &load_font_config),
        std::make_pair(FFT_XML_PUSH, &push_font_node),
        std::make_pair(FFT_XML_POP, &pop_font_node),
        std::make_pair(FFT_XML_SYNC, &sync_doc)
    };
}

CFXMLOpt::~CFXMLOpt() {

}

void CFXMLOpt::init_config() {
    const int Indent = 4;
    QString path = QCoreApplication::applicationDirPath() + config_path;
    QFile file(path);
    if (!file.exists()) {

        file.open(QIODevice::WriteOnly);

        doc = new QDomDocument();
        QTextStream out(&file);
        QDomNode xmlNode =
                doc->createProcessingInstruction("xml",
                                                 "version=\"1.0\", encoding=\"ISO-8859-1\"");
        doc->insertBefore(xmlNode, doc->firstChild());
        doc->save(out, Indent);
        file.close();
   } else {
        // TODO: ...
    }
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

