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
    enum ResizeDirection {
        Left = 0x00000001,
        Top = 0x00000002,
        Right = 0x00000004,
        Bottom = 0x00000008
    };

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void moveEvent(QMoveEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
public slots:
    void ShowContextMenu(const QPoint &pos);
    void hideCursor();
    void showCursor(QCursor &cursor);
    void setFullScreen();
    void setMinimumWindow();
private:
    ProcessBarNew *processBar;
    QPoint dragPosition;
    QTimer *autoHideTimer;
    int autoHideTimeOut = 1500;
    TitleBar *titleBar;
    bool needResize = false;
    ResizeDirection resizeDirection;
    int resizeMargin = 4;
    QCursor cursor = Qt::ArrowCursor;
};

}
#endif // TESTWIDGET_H
