#include <QApplication>
#include <QtWidgets>
#include "vrenderer.h"

class Test: public QWidget
{
public:
    Test(QWidget *parent) : QWidget(parent)
    {
        QLabel *lb = new QLabel("Pushhaha", this);
        QPushButton *btn = new QPushButton(this);
    }

};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VRenderer vrenderer;
    AVPlayer player;
    player.setRenderer(&vrenderer);


    QVBoxLayout *layout = new QVBoxLayout();
    Test *wdt = new Test(NULL);
    layout->addWidget(vrenderer.widget());
    layout->addWidget(new Test(NULL));
    wdt->setLayout(layout);
//    QLabel *dst = new QLabel("PushThis", vrenderer.widget());
    player.play("/Users/marcoqin/marco/01.mp4");
    wdt->show();
//    vrenderer.show();
    return a.exec();
}
