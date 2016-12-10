#include "dmtext.h"
#include <QPainterPath>
#include <QPainter>
#include <QtCore>

DMText::DMText(QString &text) :
    QObject()
{
    _text = text;
    _color = defaultColor;
    _fontSize = defaultFontSize;
    _font.setPixelSize(_fontSize);
}

void DMText::draw(QPainter &painter)
{
//    qDebug() << "DMText draw called";
//    qDebug() << _text;
//    qDebug() << _pos;
//    qDebug() << _color;
//    painter.setPen(QColor(100, 100, 200, 255));
//    QFont font;
//    font.setPixelSize(24);
//    painter.setFont(font);
//    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//    painter.drawLine(300, 100, 400, 400);
//    painter.drawText(QPoint(300, 100), _text);
    QPainterPath path;
    QPen pen;
    _font.setWeight(QFont::Weight::Normal);
    _font.setPixelSize(_fontSize);
    pen.setWidth(outLineWidth);
    pen.setColor(outLineColor);
    painter.setFont(_font);
    painter.setPen(pen);

    path.addText(_pos, _font, _text);
    painter.drawPath(path);
    pen.setColor(_color);
    painter.setPen(pen);
    painter.drawText(_pos, _text);
}

void DMText::caculateRect()
{
    QFontMetrics fm(_font);
    _width = fm.width(_text);
    _height = fm.height();
}
