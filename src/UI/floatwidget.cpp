#include "floatwidget.h"

using namespace UI;

FloatWidget::FloatWidget(QWidget *parent) :
    QWidget(parent)
{
    setMouseTracking(true);
    setWindowFlags(Qt::Tool |
                   Qt::FramelessWindowHint |
                   Qt::WindowStaysOnTopHint |
                   Qt::X11BypassWindowManagerHint |
                   Qt::NoDropShadowWindowHint |
                   Qt::WindowSystemMenuHint |
                   Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAutoFillBackground(true);
    backgroundColor = QColor(100, 96, 87, backgroundAlpha);
    qDebug() << mapToParent(QPoint(320,127));
    move(parent->mapToGlobal(QPoint(320,127)));
}

void FloatWidget::setBackgroundColor(QColor color)
{
    backgroundColor = color;
}

void FloatWidget::setBackgroundAlpha(int alpha)
{
    backgroundAlpha = alpha;
    backgroundColor.setAlpha(alpha);
}

void FloatWidget::setBackgroundAlpha(float alpha)
{
    if (alpha > 1 || alpha < 0){
        return;
    }
    int a = (int)(alpha * 255);
    setBackgroundAlpha(a);
}

void FloatWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), backgroundColor);
}
