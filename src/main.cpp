#include <QApplication>
#include <QtWidgets>
#include "vrenderer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VRenderer vrenderer;
    AVPlayer player;
    player.setRenderer(&vrenderer);
    vrenderer.show();

    player.play("/Users/marcoqin/marco/01.mp4");

    return a.exec();
}
