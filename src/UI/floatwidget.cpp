#include "floatwidget.h"
#include <string>
#include <sstream>
#include <iostream>
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
    backgroundMask = new QFrame(this);
    setBackgroundColor(QColor(100, 96, 87, backgroundAlpha));
}

void FloatWidget::applyBackgroundColorEffect()
{
    std::stringstream styleStream;
    int r, g, b, a;
    backgroundColor.getRgb(&r, &g, &b, &a);
    styleStream << "QFrame{background:rgba("
          << r << ","
          << g << ","
          << b << ","
          << a * 100 / 255 << "%);"
          << "border-radius:" << radius << "px;"
          << "}";
    std::string style = styleStream.str();
    qDebug() << style.c_str();
    backgroundMask->setStyleSheet(style.c_str());
}

void FloatWidget::setBackgroundColor(QColor color)
{
    backgroundColor = color;
    applyBackgroundColorEffect();
}

void FloatWidget::setBackgroundAlpha(int alpha)
{
    backgroundAlpha = alpha;
    backgroundColor.setAlpha(alpha);
    setBackgroundColor(backgroundColor);
}

void FloatWidget::setBackgroundAlpha(float alpha)
{
    if (alpha > 1 || alpha < 0){
        return;
    }
    int a = (int)(alpha * 255);
    setBackgroundAlpha(a);
}

void FloatWidget::showEvent(QShowEvent *event){
    backgroundMask->resize(width(), height());
    QWidget::showEvent(event);
}

void FloatWidget::resetPosition(QWidget *parent)
{
    QPoint global;
    switch (position) {
    case Center:
        global = parent->mapToGlobal(parent->rect().center());
        move(global.x() - width() / 2, global.y() - height() / 2);
        break;
    case TopLeft:
        global = parent->mapToGlobal(parent->rect().topLeft());
        move(global.x(), global.y());
        break;
    case TopRight:
        global = parent->mapToGlobal(parent->rect().topRight());
        move(global.x() - width(), global.y());
        break;
    case TopCenter:
        global = parent->mapToGlobal(QPoint(parent->width() / 2, 0));
        move(global.x() - width() / 2, global.y());
        break;
    case LeftCenter:
        global = parent->mapToGlobal(QPoint(0, parent->height() / 2));
        move(global.x(), global.y() - height() / 2);
        break;
    case RightCenter:
        global = parent->mapToGlobal(QPoint(parent->width(), parent->height() / 2));
        move(global.x() - width(), global.y() - height() / 2);
        break;
    case BottomLeft:
        global = parent->mapToGlobal(parent->rect().bottomLeft());
        move(global.x(), global.y() - height());
        break;
    case BottomCenter:
        global = parent->mapToGlobal(QPoint(parent->width() / 2, parent->height()));
        move(global.x() - width() / 2, global.y() - height());
        break;
    case BottomRight:
        global = parent->mapToGlobal(parent->rect().bottomRight());
        move(global.x() - width(), global.y() - height());
        break;
    }
    if (useCustomPosOffset) {
        QPoint cur = pos();
        cur += customPosOffset;
        move(cur);
    }
}

void FloatWidget::setPosition(Position pos)
{
    position = pos;
}

void FloatWidget::setCustomPositionOffset(QPoint offset)
{
    useCustomPosOffset = true;
    customPosOffset = offset;
}
