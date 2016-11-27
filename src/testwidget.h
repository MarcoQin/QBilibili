#ifndef TESTWIDGET_H
#define TESTWIDGET_H
#include <Qt>
#include <QtWidgets>

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    TestWidget(QWidget *parent);
    void popMenu();
public slots:
    void ShowContextMenu(const QPoint &pos);
};

#endif // TESTWIDGET_H
