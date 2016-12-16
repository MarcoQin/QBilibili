#include "titlebar.h"

using namespace UI;

TitleBar::TitleBar(QWidget *parent) :
    FloatWidget(parent)
{
    setRadius(0);
    setBackgroundColor(QColor(10, 10, 10, 200));
    setPosition(TopLeft);

    closeBtn = new QPushButton(this);
    closeBtn->setStyleSheet("QPushButton{border-image:url(:/Picture/close-btn.png);}"
                         "QPushButton:hover{border-image:url(:/Picture/close-btn-1.png)}");
    closeBtn->setGeometry(8, 4, 12, 12);

    minBtn = new QPushButton(this);
    minBtn->setStyleSheet("QPushButton{border-image:url(:/Picture/min-btn.png);}"
                       "QPushButton:hover{border-image:url(:/Picture/min-btn-1.png)}");
    minBtn->setGeometry(28, 4, 12, 12);

    maxBtn = new QPushButton(this);
    maxBtn->setStyleSheet("QPushButton{border-image:url(:/Picture/max-btn.png);}"
                       "QPushButton:hover{border-image:url(:/Picture/max-btn-1.png)}");
    maxBtn->setGeometry(48, 4, 12, 12);


    connect(closeBtn, SIGNAL(clicked(bool)), this, SIGNAL(closeClicked()));
    connect(minBtn, SIGNAL(clicked(bool)), this, SIGNAL(minClicked()));
    connect(maxBtn, SIGNAL(clicked(bool)), this, SIGNAL(maxClicked()));
}


void TitleBar::resetSize(QWidget *parent)
{
    resize(parent->width(), barHidht);
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    QMouseEvent* eventCopy = new QMouseEvent(*event);
    QApplication::instance()->postEvent(parent(), eventCopy);
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    QMouseEvent* eventCopy = new QMouseEvent(*event);
    QApplication::instance()->postEvent(parent(), eventCopy);
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    QMouseEvent* eventCopy = new QMouseEvent(*event);
    QApplication::instance()->postEvent(parent(), eventCopy);
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit requetMaxmiumWindow();
    event->accept();
}
