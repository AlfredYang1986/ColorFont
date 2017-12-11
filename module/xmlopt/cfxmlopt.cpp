#include "cfxmlopt.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include <QUuid>

CFFuncResults
load_font_config(const CFFuncArguments& args);
CFFuncResults
push_font_node(const CFFuncArguments& args);
CFFuncResults
pop_font_node(const CFFuncArguments& args);
CFFuncResults
sync_doc(const CFFuncArguments& args);
CFFuncResults
query_font_lib(const CFFuncArguments& args);
CFFuncResults
query_font_count(const CFFuncArguments& args);
CFFuncResults
push_times(const CFFuncArguments& args);

static const QString config_path = "/ttf_config.conf";

CFXMLOpt::CFXMLOpt() : doc(NULL), file(NULL) {

    funcs.push_back(std::make_pair(FFT_XML_LOAD, &load_font_config));
    funcs.push_back(std::make_pair(FFT_XML_PUSH, &push_font_node));
    funcs.push_back(std::make_pair(FFT_XML_POP, &pop_font_node));
    funcs.push_back(std::make_pair(FFT_XML_SYNC, &sync_doc));
    funcs.push_back(std::make_pair(FFT_XML_QUERY, &query_font_lib));
    funcs.push_back(std::make_pair(FFT_XML_COUNT, &query_font_count));
    funcs.push_back(std::make_pair(FFT_XML_PUSH_TIMES, &push_times));
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

    if (file) {
        file->close();
        delete file;
    }

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
load_font_config(const CFFuncArguments& ) {
    CFModuleManagement* cfmm =
            CFModuleManagement::queryInstance();
    CFXMLOpt* xml = (CFXMLOpt*)cfmm->queryModuleInstance(FFT_XML_MODULE);

    if (xml->doc == NULL) {
        xml->init_config();
    }

    QDomElement root = xml->doc->documentElement();
    QDomNodeList nodes = root.childNodes();
    for (int index = 0; index < nodes.count(); ++index) {
        QDomNode node = nodes.at(index);
        QDomNamedNodeMap map = node.attributes();
        QString idx = map.namedItem("index").toAttr().value();
        int cat = map.namedItem("cat").toAttr().value().toInt();
        QString path = map.namedItem("path").toAttr().value();
        FT_ULong charcode = map.namedItem("charcode").toAttr().value().toLongLong();
        int times = 0;
        QDomNode times_node = map.namedItem("times"); //.toAttr().value().toLongLong();
        if (times_node.isNull()) {
            times = 0;
        } else {
            times = times_node.toAttr().value().toInt();
        }

        QString str_uuid = 0;
        QDomNode uuid_node = map.namedItem("uuid"); //.toAttr().value().toLongLong();
        if (uuid_node.isNull()) {
            str_uuid = QUuid::createUuid().toString();
        } else {
            str_uuid = uuid_node.toAttr().value();
        }


        exchange_type et = {
            str_uuid,
            idx,
            cat,
            path,
            charcode,
            times
        };

        xml->lst.push_back(et);
    }

    return CFFuncResults();
}

CFFuncResults
push_font_node(const CFFuncArguments& args) {

    FT_ULong charcode = args.getV("charcode").value<FT_ULong>();
    QString path = args.getV("path").value<QString>();
    QString file_name = path.right(path.length() - path.lastIndexOf('/') - 1);

    QString index = args.getV("index").value<QString>();
    int cat = args.getV("cat").value<int>();

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFXMLOpt* xml = (CFXMLOpt*)cfmm->queryModuleInstance(FFT_XML_MODULE);

    QDomDocument* doc = xml->doc;
    QDomElement root = doc->documentElement();

    QDomElement new_ele = doc->createElement("char");
    QString str_uuid = QUuid::createUuid().toString();
    new_ele.setAttribute("uuid", str_uuid);
    new_ele.setAttribute("charcode", (qlonglong)charcode);
    new_ele.setAttribute("path", file_name);
    new_ele.setAttribute("cat", cat);
    new_ele.setAttribute("index", index);
    new_ele.setAttribute("times", 0);
    root.appendChild(new_ele);

//    QFile* file = xml->file;
//    if (file->exists()) {
//        file->close();
//        file->remove();
//        file->open(QIODevice::WriteOnly);
//    }
//    const int Indent = 3;
//    QTextStream out(file);
//    doc->save(out, Indent);

    return CFFuncResults();
}

CFFuncResults
pop_font_node(const CFFuncArguments& args) {
    return CFFuncResults();
}

CFFuncResults
sync_doc(const CFFuncArguments&) {
    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFXMLOpt* xml = (CFXMLOpt*)cfmm->queryModuleInstance(FFT_XML_MODULE);

    QFile* file = xml->file;
    if (file->exists()) {
        file->close();
        file->remove();
        file->open(QIODevice::WriteOnly);
    }
    const int Indent = 3;
    QTextStream out(file);
    xml->doc->save(out, Indent);

    return CFFuncResults();
}

CFFuncResults
query_font_lib(const CFFuncArguments& args) {
    const int LIB_PAGE_COUNT = 48;
    int page = args.getV("page").value<int>();

    CFModuleManagement* cfmm =
            CFModuleManagement::queryInstance();
    CFXMLOpt* xml = (CFXMLOpt*)cfmm->queryModuleInstance(FFT_XML_MODULE);

//    QList<exchange_type>::const_iterator citer = xml->lst.begin();

    QList<exchange_type> *result = new QList<exchange_type>();
    int start = page * LIB_PAGE_COUNT;
    int end = (page + 1) * LIB_PAGE_COUNT;
    for (int cur_index = start; cur_index < end; ++cur_index) {
        if (cur_index < xml->lst.size()) {
            exchange_type tmp = xml->lst.at(cur_index);
            result->push_back(tmp);
        }
    }

    QVariant v;
    v.setValue(result);

    CFFuncResults reVal;
    reVal.pushV("lst", v);

    return reVal;
}

CFFuncResults
query_font_count(const CFFuncArguments& ) {
    const int LIB_PAGE_COUNT = 48;
    CFModuleManagement* cfmm =
            CFModuleManagement::queryInstance();
    CFXMLOpt* xml = (CFXMLOpt*)cfmm->queryModuleInstance(FFT_XML_MODULE);

    int count = xml->lst.size();


    CFFuncResults reVal;

    {
        QVariant v;
        v.setValue(count);
        reVal.pushV("count", v);
    }

    {
        int pc = count / LIB_PAGE_COUNT + 1;
        QVariant v;
        v.setValue(pc);
        reVal.pushV("pc", v);
    }

    return reVal;
}

CFFuncResults
push_times(const CFFuncArguments& args) {
    const int LIB_PAGE_COUNT = 48;
    int page = args.getV("page").value<int>();
    int index = args.getV("index").value<int>();

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFXMLOpt* xml = (CFXMLOpt*)cfmm->queryModuleInstance(FFT_XML_MODULE);

    int i = (page - 1) * LIB_PAGE_COUNT + index;
    ++(xml->lst[i].times);

    return CFFuncResults();
}
