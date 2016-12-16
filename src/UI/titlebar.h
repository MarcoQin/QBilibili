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
    void requetMaxmiumWindow();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
private:
    int barHidht = 20;
    QPushButton *closeBtn;
    QPushButton *maxBtn;
    QPushButton *minBtn;
};

}
#endif // TITLEBAR_H
