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
    void setPosition(QPointF &pos);
    QPointF &getPosition();
    void setColor(QColor &color);
    QColor &getColor();
    void setText(QString &text);
    QString &getText();
    void setFontSize(int size);
    void setFont(QString &fontFamily);
    QFont &getFont();
    void setOutLIne(bool outLine);
    void setOutLineWidth(int width);
    void setAlpha(int alpha);
    int getAlpha();
    int width();
    int height();
private:
    int defaultFontSize = 24;
    QString _text;
    QColor _color;
    QFont _font;
    QPointF _pos = QPointF(0.0, 0.0);
    int _fontSize;
    bool _outLine = true;
    int outLineWidth = 5;
    int _width;
    int _height;
    int _alpha = 255;
    QColor defaultColor = QColor(255, 255, 255, _alpha);
    QColor outLineColor = QColor(0, 0, 0, _alpha);
    void caculateRect();
};

#endif // DMTEXT_H
