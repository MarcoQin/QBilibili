#include <QApplication>
#include <QtWidgets>
#include "vrenderer.h"
#include "testwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestWidget *wdt = new TestWidget(NULL);
    VRenderer *vrenderer = new VRenderer(NULL);
    AVPlayer player;
    player.setRenderer(vrenderer);


    QStackedLayout *layout = new QStackedLayout();
//    QVBoxLayout *layout = new QVBoxLayout();
//    layout->setStackingMode(QStackedLayout::StackOne);

    layout->addWidget(vrenderer->widget());
//    TestWidget *wd = new TestWidget(NULL);
//    layout->addWidget(wd);

    wdt->setLayout(layout);
//    QLabel *dst = new QLabel("PushThis", vrenderer.widget());
    player.play("/Users/marcoqin/marco/01.mp4");

    wdt->show();
    wdt->popMenu();
//    layout->setCurrentWidget(wd);
//    vrenderer.show();
    return a.exec();
}
