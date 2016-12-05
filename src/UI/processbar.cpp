#include "processbar.h"
using namespace UI;

ProcessBar::ProcessBar(QWidget *parent) :
    QWidgetAction(parent)
{
}

QWidget* ProcessBar::createWidget(QWidget *parent)
{
    return new Bar(parent);
}

Bar::Bar(QWidget *parent) :
   QWidget(parent)
{
    setupUI();
}

void Bar::setupUI()
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
    mainLayout->addWidget(timeSlider, 1, 1, 1, 14 + baseWidth * 2);

    setLayout(mainLayout);
}
