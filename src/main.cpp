#include <QApplication>
#include <QtWidgets>
#include "vrenderer.h"
#include "UI/mainwindow.h"
#include <QtAV/Statistics.h>
#include "lua/luamanager.h"
#include <IOKit/pwr_mgt/IOPMLib.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LuaManager::instance();
    UI::MainWindow *wdt = new UI::MainWindow(NULL);
    wdt->show();

    // prevent macOS from sleep
    IOPMAssertionID assertionID;
    IOReturn success = IOPMAssertionCreateWithName(kIOPMAssertionTypeNoDisplaySleep,kIOPMAssertionLevelOn, CFSTR("Describe Activity Type"), &assertionID);
    if (success == kIOReturnSuccess)
    {
        qDebug() << "SUCCESS PREVENT macOS SLEEP";
//        success = IOPMAssertionRelease(assertionID);
            //  The system will be able to sleep again.
    }
    return a.exec();
}
