#ifndef POPMENU_H
#define POPMENU_H
#include <QWidgetAction>

class PopMenu : public QWidgetAction
{
    Q_OBJECT
public:
    explicit PopMenu(QWidget * parent);
protected:
    QWidget * createWidget(QWidget *parent);
};

#endif // POPMENU_H
