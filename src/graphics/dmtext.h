#ifndef DMTEXT_H
#define DMTEXT_H
#include <Qt>
#include <QObject>
#include <QWidget>

class DMText : public QObject
{
    Q_OBJECT
public:
    DMText(QString &text);
    void draw(QPainter &painter);
//    void setPosition(QPoint &pos);
//    QPoint &getPosition();
//    void setColor(QColor &color);
//    QColor &getColor();
//    void setText(QString &text);
//    QString &getText();
//    void setFont(QFont &font);
//    QFont &getFont();
//    void setOutLIne(bool outLine);
//    void setOutLineWidth(int width);
//    int width();
//    int height();
private:
    int defaultFontSize = 24;
    QColor defaultColor = QColor(255, 255, 255, 200);
    QColor outLineColor = QColor(0, 0, 0, 200);
    QString _text;
    QColor _color;
    QFont _font;
    QPoint _pos = QPoint(300, 100);
    int _fontSize;
    bool _outLine = false;
    int outLineWidth = 5;
    int _width;
    int _height;
    int _alpha = 255;
    void caculateRect();
};

#endif // DMTEXT_H
