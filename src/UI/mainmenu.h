#ifndef MAINMENU_H
#define MAINMENU_H
#include <Qt>
#include <QtWidgets>
#include "floatwidget.h"

namespace UI {

class MainMenu : public FloatWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget * parent);
signals:
    void newFileOpened(QString fileName);
    void stopTimer();
protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
private:
    QPushButton *openBtn;
    QPushButton *openURL;
    void setupUI();
    void connectSignals();
private slots:
    void openFile();
};


}
#endif // MAINMENU_H
