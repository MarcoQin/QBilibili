#include <QApplication>
#include <QtWidgets>
#include "vrenderer.h"
#include "UI/mainwindow.h"
#include <QtAV/Statistics.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UI::MainWindow *wdt = new UI::MainWindow(NULL);

//    VRenderer *rd1 = new VRenderer(NULL);
//    AVPlayer p1;
//    p1.setRenderer(rd1);
//    layout->addWidget(rd1->widget(), 0, 1);

    AVPlayer *player = wdt->getPlayer();
    wdt->getPlayer()->play("/Users/marcoqin/marco/01.mp4");
    // wdt->getPlayer()->play("http://live-play-2.acgvideo.com/live/live_374377_4093634.flv?wsSecret=e254bd86b3a21515c9dd00be12f635b2&wsTime=581f53e5");
//    qDebug() << player.statistics().video.metadata;
//    p1.play("/Users/marcoqin/marco/01.mp4");

    wdt->show();
    wdt->popMenu();
    qDebug() << player->statistics().video_only.width;
    qDebug() << player->statistics().video_only.height;
    qDebug() << player->statistics().video_only.coded_width;
    qDebug() << player->statistics().video_only.coded_height;

    // wdt->resize(QSize(player->statistics().video_only.width / 2, player->statistics().video_only.height / 2));

    return a.exec();
}
