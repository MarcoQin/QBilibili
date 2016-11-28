#ifndef TESTWIDGET_H
#define TESTWIDGET_H
#include <Qt>
#include <QtWidgets>

namespace UI {

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent);
    void popMenu();
    void mouseMoveEvent(QMouseEvent *e);
public slots:
    void ShowContextMenu(const QPoint &pos);
};

}
#endif // TESTWIDGET_H
