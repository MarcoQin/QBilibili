#include <QApplication>
#include <QtWidgets>
#include "vrenderer.h"
#include "UI/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UI::MainWindow *wdt = new UI::MainWindow(NULL);
    VRenderer *vrenderer = new VRenderer(NULL);
    AVPlayer player;
    player.setRenderer(vrenderer);


    QGridLayout *layout = new QGridLayout();
    layout->setSizeConstraint(QLayout::SetMaximumSize);
    layout->setSpacing(1);
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);

//    VRenderer *rd1 = new VRenderer(NULL);
//    AVPlayer p1;
//    p1.setRenderer(rd1);
//    layout->addWidget(rd1->widget(), 0, 1);

    layout->addWidget(vrenderer->widget(), 0, 0);

    wdt->setLayout(layout);
    player.play("/Users/marcoqin/marco/01.mp4");
//    p1.play("/Users/marcoqin/marco/01.mp4");

    wdt->show();
    wdt->popMenu();

    return a.exec();
}
