#include "processbarnew.h"
using namespace UI;

ProcessBarNew::ProcessBarNew(QWidget *parent) :
    FloatWidget(parent)
{
    setupUI();
    // int dark = 20;
    // setBackgroundColor(QColor(100 - dark, 96 - dark, 87 - dark));
    setBackgroundColor(QColor(42, 42, 42));
    setBackgroundAlpha(0.8f);
    setPosition(BottomCenter);
    setCustomPositionOffset(QPoint(0, -40));
}


void ProcessBarNew::setupUI()
{
    prev = new QPushButton(this);
    prev->setStyleSheet("border-image:url(:/Picture/prev_episode.png);min-width:24px; min-height:24px;");
    play = new QPushButton(this);
    play->setStyleSheet("border-image:url(:/Picture/b_play.png);min-width:24px; min-height:24px;");
    next = new QPushButton(this);
    next->setStyleSheet("border-image:url(:/Picture/next_episode.png);min-width:24px; min-height:24px;");

    timeSlider = new QSlider(this);
    timeSlider->setOrientation(Qt::Horizontal);
    QFile f(":/qss/slider.qss");
    if (!f.exists()) {
        qDebug() << "slider.qss not exists!!";
    } else {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        timeSlider->setStyleSheet(ts.readAll());
        f.close();
    }

    QString labelStyle = "QLabel{color:rgba(219, 199, 188, 100%)}";
    timePass = new QLabel(this);
    timePass->setStyleSheet(labelStyle);
    timePass->setText(" 00:00");
    timeAll = new QLabel(this);
    timeAll->setStyleSheet(labelStyle);
    timeAll->setText(" 00:00");


    // new stuffs
    resize(440, 64);
    prev->setGeometry(160, 13, 24, 24);
    play->setGeometry(210, 13, 24, 24);
    next->setGeometry(256, 13, 24, 24);
    timeSlider->setGeometry(58, 40, 324, 17);
    timePass->setGeometry(4, 40, 42, 14);
    timeAll->setGeometry(388, 40, 42, 14);

}
