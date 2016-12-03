#include <QApplication>
#include <QtWidgets>
#include "vrenderer.h"
#include "UI/mainwindow.h"
#include <QtAV/Statistics.h>

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
//    qDebug() << player.statistics().video.metadata;
//    p1.play("/Users/marcoqin/marco/01.mp4");

    wdt->show();
    wdt->popMenu();
    qDebug() << player.statistics().video_only.width;
    qDebug() << player.statistics().video_only.height;
    qDebug() << player.statistics().video_only.coded_width;
    qDebug() << player.statistics().video_only.coded_height;

    wdt->resize(QSize(player.statistics().video_only.width / 2, player.statistics().video_only.height / 2));

    return a.exec();
}
