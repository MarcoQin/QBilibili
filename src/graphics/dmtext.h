#ifndef DMTEXT_H
#define DMTEXT_H
#include <Qt>
#include <QObject>
#include <QWidget>

class DMText : public QObject
{
    Q_OBJECT
public:
    DMText(QString &text, QColor &color, QFont &font);
    DMText(QString &text, QColor &color);
    DMText(QString &text);
    void draw(QPainter &painter);
    void setPosition(QPoint &pos);
    QPoint &getPosition();
    void setColor(QColor &color);
    QColor &getColor();
    void setText(QString &text);
    QString &getText();
    void setFont(QFont &font);
    QFont &getFont();
    void setOutLIne(bool outLine);
    void setOutLineWidth(int width);
    int width();
    int height();
private:
    QString _text;
    QColor _color;
    QFont _font;
    QPoint _pos;
    bool _outLine = false;
    int outLineWidth = 5;
    int _width;
    int _height;
};

#endif // DMTEXT_H
