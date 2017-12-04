#include "cfmainwindow.h"
#include "prevdialog/cfprevdialog.h"

#include <QApplication>
#include <QSplashScreen>
#include <QDateTime>
#include <QtOpenGL>
#include "module/modulemanagement/cfmm.h"
#include "common/funcargs/cfargs.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    QSplashScreen* splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/resource/screen.png"));
    splash->show();

    QTime dieTime = QTime::currentTime().addMSecs(1500);

    CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
    cfmm->pushMessage(FFT_XML_MODULE, FFT_XML_LOAD, CFFuncArguments());

    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    CFMainWindow w;

    QVariant v;
    v.setValue(&w);
    CFFuncArguments args;
    args.pushV("main_window", v);
    cfmm->pushMessage(QUERY_MODULE, QUERY_PUSH_MAIN_WINDOW, args);

    w.showMaximized();

    splash->finish(&w);
    return a.exec();
}
