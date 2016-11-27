#include "testwidget.h"
#include "popmenu.h"

TestWidget::TestWidget(QWidget *parent): QWidget(parent)
{
    setMouseTracking(true);
    setAcceptDrops(true);
    resize(800, 600);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));
}


void TestWidget::popMenu()
{
    ShowContextMenu(QPoint(100, 100));
}

void TestWidget::ShowContextMenu(const QPoint &pos)
    {
        qDebug()<<":popuprightclickMenu"; //just to see if activated
       QMenu contextMenu(tr("Context menu"), this);

       QAction action1("Remove Data Point", this);
//       connect(&action1, SIGNAL(triggered()), this, SLOT(removeDataPoint()));
       contextMenu.addAction(&action1);


       PopMenu *popMenuAction = new PopMenu(this);
       contextMenu.addAction(popMenuAction);



       contextMenu.exec(mapToGlobal(pos));
//       contextMenu.popup(pos);
    }
