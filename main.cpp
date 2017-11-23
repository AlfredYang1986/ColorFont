#include "cfmainwindow.h"
#include "prevdialog/cfprevdialog.h"

#include <QApplication>
#include <QSplashScreen>
#include <QDateTime>
#include <QtOpenGL>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    QSplashScreen* splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/resource/screen.png"));
    splash->show();

    QTime dieTime = QTime::currentTime().addMSecs(1500);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    CFMainWindow w;
    w.showMaximized();

    splash->finish(&w);
    return a.exec();
}
