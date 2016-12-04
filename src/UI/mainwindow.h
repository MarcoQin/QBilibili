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
    static constexpr int None = 0x00000000;
    static constexpr int Left = 0x00000001;
    static constexpr int Top = 0x00000002;
    static constexpr int Right = 0x00000004;
    static constexpr int Bottom = 0x00000008;

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
    QPoint pressPosition;
    int pressWidth;
    int pressHeight;
    QTimer *autoHideTimer;
    int autoHideTimeOut = 1500;
    TitleBar *titleBar;
    bool needResize = false;
    int resizeDirection = None;
    int resizeMargin = 5;
    QCursor cursor = Qt::ArrowCursor;
    int delta_x = 0;
    int delta_y = 0;
};

}
#endif // TESTWIDGET_H
