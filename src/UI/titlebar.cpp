#include "titlebar.h"

using namespace UI;

TitleBar::TitleBar(QWidget *parent) :
    FloatWidget(parent)
{
    setRadius(0);
    setBackgroundColor(QColor(10, 10, 10, 200));
    setPosition(TopLeft);

    close = new QPushButton(this);
    close->setStyleSheet("QPushButton{border-image:url(:/Picture/close-btn.png);}"
                         "QPushButton:hover{border-image:url(:/Picture/close-btn-1.png)}");
    close->setGeometry(8, 4, 12, 12);

    min = new QPushButton(this);
    min->setStyleSheet("QPushButton{border-image:url(:/Picture/min-btn.png);}"
                       "QPushButton:hover{border-image:url(:/Picture/min-btn-1.png)}");
    min->setGeometry(28, 4, 12, 12);

    max = new QPushButton(this);
    max->setStyleSheet("QPushButton{border-image:url(:/Picture/max-btn.png);}"
                       "QPushButton:hover{border-image:url(:/Picture/max-btn-1.png)}");
    max->setGeometry(48, 4, 12, 12);
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

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    QMouseEvent* eventCopy = new QMouseEvent(*event);
    QApplication::instance()->postEvent(parent(), eventCopy);
}
