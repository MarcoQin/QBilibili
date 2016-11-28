#include <QApplication>
#include <QtWidgets>
#include "vrenderer.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UI::MainWindow *wdt = new UI::MainWindow(NULL);
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
    QMouseEvent event(QEvent::MouseButtonPress, QPoint(0, 0), Qt::LeftButton, Qt::AllButtons, Qt::NoModifier);
    qApp->notify(wdt, &event);
//    layout->setCurrentWidget(wd);
//    vrenderer.show();
    return a.exec();
}
