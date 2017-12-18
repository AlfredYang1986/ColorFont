#include "cfxmlopt.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include <QUuid>
#include <QTextStream>

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

CFFuncResults
save(const CFFuncArguments& args);
CFFuncResults
save_pro_file(const CFFuncArguments& args);
CFFuncResults
save_cur_ttf_files(const CFFuncArguments& args);

CFFuncResults
load(const CFFuncArguments& args);
CFFuncResults
load_pro_file(const CFFuncArguments& args);
CFFuncResults
load_cur_ttf_files(const CFFuncArguments& args);

static const QString config_path = "/ttf_config.conf";

CFXMLOpt::CFXMLOpt() : doc(NULL), file(NULL) {

    funcs.push_back(std::make_pair(FFT_XML_LOAD, &load_font_config));
    funcs.push_back(std::make_pair(FFT_XML_PUSH, &push_font_node));
    funcs.push_back(std::make_pair(FFT_XML_POP, &pop_font_node));
    funcs.push_back(std::make_pair(FFT_XML_SYNC, &sync_doc));
    funcs.push_back(std::make_pair(FFT_XML_QUERY, &query_font_lib));
    funcs.push_back(std::make_pair(FFT_XML_COUNT, &query_font_count));
    funcs.push_back(std::make_pair(FFT_XML_PUSH_TIMES, &push_times));

    funcs.push_back(std::make_pair(FFT_XML_SAVE_CURRENT, &save));
    funcs.push_back(std::make_pair(FFT_XML_SAVE_CURRENT_PRO, &save_pro_file));
    funcs.push_back(std::make_pair(FFT_XML_SAVE_TTF_FILES, &save_cur_ttf_files));

    funcs.push_back(std::make_pair(FFT_XML_LOAD_CURRENT, &load));
    funcs.push_back(std::make_pair(FFT_XML_LOAD_CURRENT_PRO, &load_pro_file));
    funcs.push_back(std::make_pair(FFT_XML_LOAD_TTF_FILES, &load_cur_ttf_files));
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

CFFuncResults
save(const CFFuncArguments& args) {
    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    cfmm->pushMessage(FILE_MODULE, FILE_SAVE_DIR, args);
    cfmm->pushMessage(FFT_XML_MODULE, FFT_XML_SAVE_CURRENT_PRO, args);
    cfmm->pushMessage(FFT_XML_MODULE, FFT_XML_SAVE_TTF_FILES, args);

    return CFFuncResults();
}

CFFuncResults
save_pro_file(const CFFuncArguments& args) {
    QString save_path = args.getV("save_path").value<QString>();
    QVector<std::pair<FT_Face, FT_ULong> > chars = args.getV("chars").value<QVector<std::pair<FT_Face, FT_ULong> > >();

    qDebug() << "chars size is : " << chars.size();

    QFile file(save_path + "/project.pro");
    if (file.exists()) {
//        file.remove();
        QFile::remove(save_path + "/project.pro");
    }

    bool result;

    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Error: cannot create new file : " << save_path;
        result = false;
    } else {
        QDomDocument* doc = new QDomDocument();
        QTextStream out(&file);
        QDomNode xmlNode =
                doc->createProcessingInstruction("xml",
                                                 "version=\"1.0\" encoding=\"ISO-8859-1\"");

        doc->insertBefore(xmlNode, doc->firstChild());

        QDomNode rootNode = doc->createElement("project");
        doc->insertAfter(rootNode, xmlNode);

        CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
//        cfmm->pushMessage(FFT_MODULE, )

        for (int index = 0; index < chars.size(); ++index) {

            FT_ULong charcode = chars[index].second;
            FT_Face f = chars[index].first;

            CFFuncArguments arg_path_by_face;
            QVariant v;
            v.setValue(f);
            arg_path_by_face.pushV("face", v);

            CFFuncResults re_path_by_face =
                cfmm->pushMessage(FFT_MODULE, FFT_QUERY_PATH_BY_FACE, arg_path_by_face);

            QDomElement new_ele = doc->createElement("char");
            QString str_uuid = QUuid::createUuid().toString().replace('{', "").replace('}', "");
            new_ele.setAttribute("uuid", str_uuid);
            new_ele.setAttribute("charcode", (qlonglong)charcode);

            QString ttf_path = re_path_by_face.getV("path").value<QString>();
            new_ele.setAttribute("path",
                                 ttf_path.right(ttf_path.size() - ttf_path.lastIndexOf("/") - 1));
            rootNode.appendChild(new_ele);
        }

        const int Indent = 4;
        doc->save(out, Indent);
        delete doc;
        file.close();
        result = true;
    }

    return CFFuncResults();
}

CFFuncResults
save_cur_ttf_files(const CFFuncArguments &args) {
    QVector<FT_Face> faces = args.getV("faces").value<QVector<FT_Face> >();
    QString save_path = args.getV("save_path").value<QString>();

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFFuncResults re_paths = cfmm->pushMessage(FFT_MODULE, FFT_QUERY_PATHS_FROM_FACES, args);

    QVector<QString> used_paths = re_paths.getV("paths").value<QVector<QString> >();
    for (int index = 0; index < used_paths.size(); ++index) {
        QString tmp_file = used_paths[index];
        if (!tmp_file.startsWith(save_path)) {
            QString tmp_ttf = tmp_file.right(tmp_file.size() - tmp_file.lastIndexOf("/") - 1);
            QString new_file = save_path + "/ttf_dir/" + tmp_ttf;
            QFile::copy(tmp_file, new_file);
        }
    }

    return CFFuncResults();
}

CFFuncResults
load(const CFFuncArguments& args) {
    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    cfmm->pushMessage(FILE_MODULE, FILE_CHECK_SAVE_DIR, args);
//    cfmm->pushMessage(FFT_XML_MODULE, FFT_XML_SAVE_CURRENT_PRO, args);
//    cfmm->pushMessage(FFT_XML_MODULE, FFT_XML_SAVE_TTF_FILES, args);

    return CFFuncResults();
}

CFFuncResults
load_pro_file(const CFFuncArguments& args) {
    QString save_path = args.getV("path").value<QString>();

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();

    bool result;
    QFile* file = new QFile(save_path);

    if (!file->open(QIODevice::ReadOnly | QFile::Text)) {
        qDebug() << "Error: cannot open file : " << save_file;
        result = false;
        exit(1);
    }

    QString errorStr;
    int errorLine;
    int errorColum;

    QDomDocument* doc = new QDomDocument();
    if (!doc->setContent(file, false, &errorStr, &errorLine, &errorColum)) {
        qDebug() << "Error: Parse error at line " << errorLine << ", "
                 << "column " << errorColum << ": "
                 << errorStr;
        result = false;
        exit(1);
    } else {
        result = true;

        QVector<std::pair<QString, FT_ULong> > char_paths;
        QVector<std::pair<FT_Face, FT_ULong> > chars;

        QDomElement root = doc->documentElement();
        QDomNodeList nodes = root.childNodes();
        for (int index = 0; index < nodes.count(); ++index) {
            QDomNode node = nodes.at(index);
            QDomNamedNodeMap map = node.attributes();

            QString ttr_path = save_path.left(save_path.size() - save_path.lastIndexOf("/") - 1) + "/ttf_dir/";

        }
    }

    return CFFuncResults();
}

CFFuncResults
load_cur_ttf_files(const CFFuncArguments& args) {
    return CFFuncResults();
}
