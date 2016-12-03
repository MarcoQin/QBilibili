#ifndef TESTWIDGET_H
#define TESTWIDGET_H
#include <Qt>
#include <QtWidgets>

#include "processbarnew.h"
#include "titlebar.h"

namespace UI {

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent);
    void popMenu();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void moveEvent(QMoveEvent *event);
    void mousePressEvent(QMouseEvent *event);
public slots:
    void ShowContextMenu(const QPoint &pos);
    void hideCursor();
    void showCursor();
private:
    ProcessBarNew *processBar;
    QPoint dragPosition;
    QTimer *autoHideTimer;
    int autoHideTimeOut = 1500;
    TitleBar *titleBar;
};

}
#endif // TESTWIDGET_H
