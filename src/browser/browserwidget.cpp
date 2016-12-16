#include "browserwidget.h"

using namespace UI;

BrowserWidget::BrowserWidget(QWidget *parent) :
    FloatWidget(parent)
{
    setMouseTracking(true);
}


void BrowserWidget::setupUI()
{
    setPosition(Center);
    setCustomPositionOffset(QPoint(0, titleOffset));
}


void BrowserWidget::resetSize(QWidget *parent)
{
    resize(parent->width() - 10, parent->height() - titleOffset);
}
