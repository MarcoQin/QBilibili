#ifndef TITLEBAR_H
#define TITLEBAR_H
#include "floatwidget.h"


namespace UI {

class TitleBar : public FloatWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent);
    void resetSize(QWidget *parent);
signals:
    void minClicked();
    void maxClicked();
    void closeClicked();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
private:
    int barHidht = 20;
    QPushButton *close;
    QPushButton *max;
    QPushButton *min;
};

}
#endif // TITLEBAR_H
