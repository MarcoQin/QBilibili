#include "titlebar.h"

using namespace UI;

TitleBar::TitleBar(QWidget *parent) :
    FloatWidget(parent)
{
    setBackgroundColor(QColor(10, 10, 10, 255));
    setPosition(TopLeft);
//    setWindowFlags(Qt::CustomizeWindowHint |  Qt::WindowCloseButtonHint | Qt::WindowFullscreenButtonHint);
    resize(600, 20);

}
