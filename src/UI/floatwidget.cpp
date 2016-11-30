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
    curPainter = QPainter(this);
    backgroundAlpha = 200;
    backgroundColor = QColor(100, 96, 87, backgroundAlpha);
}

void FloatWidget::paintEvent(QPaintEvent *)
{
    curPainter.fillRect(rect(), backgroundColor);
}
