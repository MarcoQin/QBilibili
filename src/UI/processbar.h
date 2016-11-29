#ifndef PROCESSBAR_H
#define PROCESSBAR_H
#include <QtWidgets>

namespace UI {

class ProcessBar : public QWidgetAction
{
    Q_OBJECT
public:
    explicit ProcessBar(QWidget *parent);
protected:
    QWidget * createWidget(QWidget *parent);
};

class Bar : public QWidget
{
    Q_OBJECT
public:
    Bar(QWidget *parent);
private:
    QPushButton *play;
    QPushButton *prev;
    QPushButton *next;
    QSlider *timeSlider;
    void setupUI();
};

}
#endif // PROCESSBAR_H
