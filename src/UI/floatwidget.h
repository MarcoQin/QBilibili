#ifndef MENULIKEWIDGET_H
#define MENULIKEWIDGET_H

#include <Qt>
#include <QtWidgets>

namespace UI {

class FloatWidget : public QWidget
{
    Q_OBJECT
public:
    enum Position{
        TopLeft = 0,
        Center = 1,
        BottomLeft = 2,
        TopRight = 3,
        BottomRight = 4,
        LeftCenter = 5,
        RightCenter = 6,
        TopCenter = 7,
        BottomCenter = 8,
        Custom = 9
    };
    explicit FloatWidget(QWidget *parent = 0);
    void setBackgroundColor(QColor color);
    void setBackgroundAlpha(int alpha);
    void setBackgroundAlpha(float alpha);
    void resetPosition(QWidget *parent);
    void setPosition(Position pos);

protected:
    virtual void showEvent(QShowEvent *event);



public slots:

private:
    QColor backgroundColor;
    int backgroundAlpha = 255;
    int radius = 4;
    QFrame *backgroundMask;
    void applyBackgroundColorEffect();
    Position position = TopLeft;
};

}

#endif // MENULIKEWIDGET_H
