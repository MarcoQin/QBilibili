#include <QApplication>
#include <QtWidgets>
#include "vrenderer.h"
#include "UI/mainwindow.h"
#include <QtAV/Statistics.h>
#include "lua/luamanager.h"

#ifdef __APPLE__
#include <IOKit/pwr_mgt/IOPMLib.h>
#endif


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // for webengine developer tools
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "9137");

    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/Picture/icon.png"));

    LuaManager::instance();
    UI::MainWindow *wdt = new UI::MainWindow(NULL);
    wdt->show();

#ifdef __APPLE__
    // prevent macOS from sleep
    IOPMAssertionID assertionID;
    IOReturn success = IOPMAssertionCreateWithName(kIOPMAssertionTypeNoDisplaySleep,kIOPMAssertionLevelOn, CFSTR("Describe Activity Type"), &assertionID);
    if (success == kIOReturnSuccess)
    {
        qDebug() << "SUCCESS PREVENT macOS SLEEP";
//        success = IOPMAssertionRelease(assertionID);
            //  The system will be able to sleep again.
    }
#endif


    return a.exec();
}
