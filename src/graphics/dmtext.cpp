#include "dmtext.h"
#include <QPainterPath>
#include <QPainter>

DMText::DMText(QString &text, QColor &color, int fontSize) :
    QObject(),
    _text(text),
    _color(color),
    _fontSize(fontSize)
{

}

DMText::DMText(QString &text, QColor &color) :
    QObject()
{
    DMText(text, color, defaultFontSize);
}

DMText::DMText(QString &text) :
    QObject()
{
    DMText(text, defaultColor);
}

void DMText::draw(QPainter &painter)
{
    QPainterPath path;
    QPen pen;
    _font.setWeight(QFont::Weight::Normal);
    pen.setWidth(outLineWidth);
    pen.setColor(outLineColor);
    painter.setFont(_font);
    painter.setPen(pen);

    path.addText(_pos, _font, _text);
    painter.drawPath(path);
    pen.setColor(_color);
    painter.drawText(_pos, _text);
}

void DMText::caculateRect()
{
    QFontMetrics fm(_font);
    _width = fm.width(_text);
    _height = fm.height();
}
