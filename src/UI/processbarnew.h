#ifndef PROCESSBARNEW_H
#define PROCESSBARNEW_H
#include "floatwidget.h"

namespace UI {

class ProcessBarNew : public FloatWidget
{
    Q_OBJECT
public:
    explicit ProcessBarNew(QWidget *parent);
    void setTimeOutTimer(QTimer *timer);
protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
private:
    QPushButton *play;
    QPushButton *prev;
    QPushButton *next;
    QSlider *timeSlider;
    QSlider *volSlider;
    QLabel *timePass;
    QLabel *timeAll;
    void setupUI();
    QTimer *parentAutoHideTimer;
};

}

#endif // PROCESSBARNEW_H
