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
