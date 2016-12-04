#ifndef TITLEBAR_H
#define TITLEBAR_H
#include "floatwidget.h"


namespace UI {

class TitleBar : public FloatWidget
{
public:
    explicit TitleBar(QWidget *parent);
    void resetSize(QWidget *parent);
    QPushButton *close;
    QPushButton *max;
    QPushButton *min;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
private:
    int barHidht = 20;
};

}
#endif // TITLEBAR_H
