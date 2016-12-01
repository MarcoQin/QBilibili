#ifndef PROCESSBARNEW_H
#define PROCESSBARNEW_H
#include "floatwidget.h"

namespace UI {

class ProcessBarNew : public FloatWidget
{
    Q_OBJECT
public:
    explicit ProcessBarNew(QWidget *parent);
private:
    QPushButton *play;
    QPushButton *prev;
    QPushButton *next;
    QSlider *timeSlider;
    void setupUI();
};

}

#endif // PROCESSBARNEW_H
