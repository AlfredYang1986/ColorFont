#include "cfqueryopt.h"

#include "../../cfmainwindow.h"

CFFuncResults
query_push_main_window(const CFFuncArguments& args);
CFFuncResults
query_query_main_window(const CFFuncArguments& args);

CFQueryOpt::CFQueryOpt() {
    funcs = {
        std::make_pair(QUERY_MAIN_WINDOW, &query_query_main_window),
        std::make_pair(QUERY_PUSH_MAIN_WINDOW, &query_push_main_window)
    };
}

CFQueryOpt::~CFQueryOpt() {

}

CFFuncResults
query_push_main_window(const CFFuncArguments &args) {
    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFQueryOpt* opt = (CFQueryOpt*)cfmm->queryModuleInstance(QUERY_MODULE);

    CFMainWindow* w = args.getV("main_window").value<CFMainWindow*>();
    opt->main_window = w;
    return CFFuncResults();
}

CFFuncResults
query_query_main_window(const CFFuncArguments &) {
    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    CFQueryOpt* opt = (CFQueryOpt*)cfmm->queryModuleInstance(QUERY_MODULE);

    QVariant v;
    v.setValue(opt->main_window);

    CFFuncResults reVal;
    reVal.pushV("main_window", v);

    return reVal;
}
