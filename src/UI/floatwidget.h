#ifndef MENULIKEWIDGET_H
#define MENULIKEWIDGET_H

#include <Qt>
#include <QtWidgets>

namespace UI {

class FloatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FloatWidget(QWidget *parent = 0);
    void setBackgroundColor(QColor color);
    void setBackgroundAlpha(int alpha);
    void setBackgroundAlpha(float alpha);

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    QColor backgroundColor;
    int backgroundAlpha = 255;
};

}

#endif // MENULIKEWIDGET_H
