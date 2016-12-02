#include "processbarnew.h"
using namespace UI;

ProcessBarNew::ProcessBarNew(QWidget *parent) :
    FloatWidget(parent)
{
    setupUI();
    int dark = 20;
    setBackgroundColor(QColor(100 - dark, 96 - dark, 87 - dark));
    setBackgroundAlpha(0.8f);
    setPosition(BottomCenter);
    setCustomPositionOffset(QPoint(0, -40));
}


void ProcessBarNew::setupUI()
{
    prev = new QPushButton(this);
    prev->setStyleSheet("border-image:url(:/Picture/prev_episode.png);min-width:32px; min-height:32px;");
    play = new QPushButton(this);
    play->setStyleSheet("border-image:url(:/Picture/b_play.png);min-width:32px; min-height:32px;");
    next = new QPushButton(this);
    next->setStyleSheet("border-image:url(:/Picture/next_episode.png);min-width:32px; min-height:32px;");

    QGridLayout *mainLayout = new QGridLayout;

    int baseWidth = 10;

    mainLayout->addWidget(prev, 0, 5 + baseWidth, 1, 1);
    mainLayout->addWidget(play, 0, 7 + baseWidth, 1, 1);
    mainLayout->addWidget(next, 0, 9 + baseWidth, 1, 1);

    timeSlider = new QSlider(this);
    timeSlider->setOrientation(Qt::Horizontal);
    mainLayout->addWidget(timeSlider, 1, 0, 1, 14 + baseWidth * 2);
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(mainLayout);
}
