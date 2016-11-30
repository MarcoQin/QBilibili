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

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    QColor backgroundColor;
    int backgroundAlpha;
    QPainter curPainter;
};

}

#endif // MENULIKEWIDGET_H
