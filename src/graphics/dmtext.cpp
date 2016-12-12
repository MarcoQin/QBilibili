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
    caculateRect();
}

void DMText::draw(QPainter &painter)
{
//    qDebug() << "DMText draw called";
//    qDebug() << _text;
//    qDebug() << _pos;
//    qDebug() << _color;
//    painter.setPen(QColor(100, 100, 200, 255));
//    QFont font;
//    font.setFamily("Apple Color Emoji");
//    font.setPixelSize(24);
//    painter.setFont(font);
//    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//    painter.drawLine(300, 100, 400, 400);
//    painter.drawText(QPoint(300, 300), _text);
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

void DMText::setPosition(QPointF &pos)
{
    // qDebug() << "setPosition: old: " <<  _pos << "new: " << pos;
    _pos = pos;
}

QPointF &DMText::getPosition()
{
    // qDebug() << "getPosiont" << _pos;
    return _pos;
}

void DMText::setColor(QColor &color)
{
    _color = color;
    _color.setAlpha(_alpha);
}

QColor &DMText::getColor()
{
    return _color;
}

void DMText::setFont(QString &fontFamily)
{
    _font.setFamily(fontFamily);
    caculateRect();
}

QFont &DMText::getFont()
{
    return _font;
}

void DMText::setOutLIne(bool outLine)
{
    _outLine = outLine;
}

void DMText::setOutLineWidth(int width)
{
    outLineWidth = width;
}

int DMText::width()
{
    return _width;
}

int DMText::height()
{
    return _height;
}

void DMText::setFontSize(int size)
{
    _fontSize = size;
    _font.setPixelSize(_fontSize);
    caculateRect();
}

void DMText::setText(QString &text)
{
    _text = text;
    caculateRect();
}

QString &DMText::getText()
{
    return _text;
}

void DMText::setAlpha(int alpha)
{
    _alpha = alpha;
    _color.setAlpha(_alpha);
    outLineColor.setAlpha(_alpha);
}

int DMText::getAlpha()
{
    return _alpha;
}
