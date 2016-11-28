#include "mainwindow.h"
#include "../popmenu.h"

using namespace UI;

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{
    setMouseTracking(true);
    setAcceptDrops(true);
    resize(800, 600);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));
}


void MainWindow::popMenu()
{
    ShowContextMenu(QPoint(100, 100));
}


class CustomQMenu : public QMenu
{
public:
    CustomQMenu(QWidget *parent = 0) : QMenu (parent){}
    virtual void mouseReleaseEvent (QMouseEvent *e)
          {
            QAction *action = activeAction();
            if (action && action->isEnabled()) {
                action->setEnabled(false);
                QMenu::mouseReleaseEvent(e);
                action->setEnabled(true);
                action->trigger();
            }
            else
                QMenu::mouseReleaseEvent(e);
          }
    virtual void leaveEvent(QEvent *) {
        qDebug() << "mouse leave";
        close();
    }
};

void MainWindow::ShowContextMenu(const QPoint &pos)
    {
        qDebug()<<":popuprightclickMenu"; //just to see if activated
//       QMenu contextMenu(tr("Context menu"), this);
       CustomQMenu contextMenu(this);

//       QAction action1("Remove Data Point", this);
//       connect(&action1, SIGNAL(triggered()), this, SLOT(removeDataPoint()));
//       contextMenu.addAction(&action1);


       PopMenu *popMenuAction = new PopMenu(this);
       contextMenu.addAction(popMenuAction);


       contextMenu.setWindowFlags(contextMenu.windowFlags() | Qt::FramelessWindowHint);
       contextMenu.setAttribute(Qt::WA_TranslucentBackground);
       contextMenu.setStyleSheet("QMenu{background:rgba(100, 96, 87, 70%);}QLabel{color:rgba(219, 199, 188, 100%);}");
       contextMenu.exec(mapToGlobal(pos));
    }

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    QPoint cur = e->pos();
    int x = cur.x(), y = cur.y(), w = width(), h = height();
//    qDebug() << x << y << w << h;
    if (isActiveWindow()) {
        if (y * 1.0 / h > 0.8) {
            ShowContextMenu(QPoint(w * 1.0 / 5, y));
        }
    }
    QWidget::mouseMoveEvent(e);
}
