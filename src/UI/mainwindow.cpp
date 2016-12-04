#include "mainwindow.h"
#include "mainmenu.h"
#include "processbar.h"

using namespace UI;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    setAcceptDrops(true);
    resize(800, 600);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    processBar = new ProcessBarNew(this);
    titleBar = new TitleBar(this);
    autoHideTimer = new QTimer(this);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));
    connect(autoHideTimer, SIGNAL(timeout()), processBar, SLOT(hide()));
    connect(autoHideTimer, SIGNAL(timeout()), titleBar, SLOT(hide()));
    connect(autoHideTimer, SIGNAL(timeout()), this, SLOT(hideCursor()));

    connect(titleBar->close, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(titleBar->min, SIGNAL(clicked(bool)), this, SLOT(setMinimumWindow()));
    connect(titleBar->max, SIGNAL(clicked(bool)), this, SLOT(setFullScreen()));

    autoHideTimer->start(autoHideTimeOut);
}

void MainWindow::hideCursor()
{
    QApplication::setOverrideCursor(Qt::BlankCursor);
}


void MainWindow::showCursor(QCursor &cursor)
{
    QApplication::setOverrideCursor(cursor);
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
signals:
    void aboutToHide()
    {
        qDebug() << "aboutToHide";
    }
};

class Test : public QWidget
{
public:
    Test(QWidget *parent) :
        QWidget(parent)
    {
//        setAutoFillBackground(true);
//        QPalette palette = this->palette();
//        palette.setColor(QPalette::Window, Qt::white);
//        this->setPalette(palette);
//        219, 199, 188
        setWindowFlags(Qt::Popup);
        QHBoxLayout* pLayout = new QHBoxLayout();
        QLabel *pLabel = new QLabel ("title");
        pLayout->addWidget (pLabel);
        QSpinBox *pSpinBox = new QSpinBox(NULL);
        pLayout->addWidget (pSpinBox);
        setLayout (pLayout);
        QLabel *timeT = new QLabel(tr("Time"), this);
        QLabel *volmT = new QLabel(tr("Volume"), this);
        QSlider *timeS = new QSlider(this);
        QSlider *volmS = new QSlider(this);
        timeS->setOrientation(Qt::Horizontal);
        volmS->setOrientation(Qt::Horizontal);
        timeS->setRange(0, 0);
        volmS->setRange(0, 100);
        timeS->setValue(0);
        pLayout->addWidget(timeT);
        pLayout->addWidget(volmT);
        pLayout->addWidget(volmS);
        pLayout->addWidget(timeS);
        QPushButton *fileB = new QPushButton(this);
        fileB->setText(tr("Open"));
        pLayout->addWidget(fileB);
        QAction *fileA = new QAction(tr("Open File"), this);
        fileA->setObjectName("File");
        connect(fileA, &QAction::triggered, [this](){
            QString _file = QFileDialog::getOpenFileName();
            qDebug() << _file;
        });
        addAction(fileA);
        connect(fileB, &QPushButton::clicked, fileA, &QAction::trigger);
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


//       MainMenu *menuPanel = new MainMenu(this);
       ProcessBar *menuPanel = new ProcessBar(this);
       contextMenu.addAction(menuPanel);


       contextMenu.setWindowFlags(contextMenu.windowFlags() | Qt::FramelessWindowHint);
       contextMenu.setAttribute(Qt::WA_TranslucentBackground);
       contextMenu.setStyleSheet("QMenu{background:rgba(100, 96, 87, 70%);}QLabel{color:rgba(219, 199, 188, 100%);}");
       contextMenu.exec(mapToGlobal(pos));
    }

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();

        QPoint cur = event->pos();
        int x = cur.x(), y = cur.y(), w = width(), h = height();
        int lx = 0, ly = 0;
        int dx = x - lx, dy = y - ly;
        int drx = w - x, dry = h - y;
        if (dry > 0 && dry < resizeMargin) {
            cursor = Qt::SizeVerCursor;
            needResize = true;
            resizeDirection = Bottom;
        } else if (dy > 0 && dy < resizeMargin) {
            cursor = Qt::SizeVerCursor;
            needResize = true;
            resizeDirection = Top;
        } else if (drx > 0 && drx < resizeMargin) {
            cursor = Qt::SizeHorCursor;
            needResize = true;
            resizeDirection = Right;
        } else if (dx > 0 && dx < resizeMargin) {
            cursor = Qt::SizeHorCursor;
            needResize = true;
            resizeDirection = Left;
        }

        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    needResize = false;
    cursor = Qt::ArrowCursor;
    event->accept();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    QPoint cur = event->pos();
    int x = cur.x(), y = cur.y(), w = width(), h = height();
    int lx = 0, ly = 0;

    if (isActiveWindow()) {
        if (!needResize) {
            cursor = Qt::ArrowCursor;
        }

        if (cursor.shape() == Qt::ArrowCursor || cursor.shape() == Qt::BlankCursor) {
            int dx = x - lx, dy = y - ly;
            int drx = w - x, dry = h - y;
            if (dry > 0 && dry < resizeMargin) {
                cursor = Qt::SizeVerCursor;
            } else if (dy > 0 && dy < resizeMargin) {
                cursor = Qt::SizeVerCursor;
            } else if (drx > 0 && drx < resizeMargin) {
                cursor = Qt::SizeHorCursor;
            } else if (dx > 0 && dx < resizeMargin) {
                cursor = Qt::SizeHorCursor;
            }
        }

        if (!processBar->isVisible()) {
            processBar->show();
            processBar->resetPosition(this);
        }
        if (!titleBar->isVisible()) {
            titleBar->show();
            titleBar->resetPosition(this);
            titleBar->resetSize(this);
        }
        showCursor(cursor);
        autoHideTimer->start(autoHideTimeOut);
    }

    /* handle drag window event*/
    if (event->buttons() & Qt::LeftButton) {
        if (!needResize) {
            move(event->globalPos() - dragPosition);
        } else {
            QPoint global = mapToGlobal(rect().topLeft());
            switch(resizeDirection) {
            case Bottom:
                setGeometry(global.x(), global.y(), w, event->globalPos().y() - global.y());
                break;
            case Right:
                setGeometry(global.x(), global.y(), event->globalPos().x() - global.x(), h);
                break;
            case Left:
                QPoint rightX = mapToGlobal(QPoint(rect().right(), 0));
                setGeometry(event->globalPos().x(), global.y(), rightX.x() - event->globalPos().x(), h);
                break;
            }
        }
        event->accept();
    }
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    if (processBar->isVisible()) {
        processBar->resetPosition(this);
    }
    if (titleBar->isVisible()) {
        titleBar->resetPosition(this);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    titleBar->resetSize(this);
    titleBar->resetPosition(this);
    processBar->resetPosition(this);
}

void MainWindow::setFullScreen()
{
    titleBar->hide();
    processBar->hide();
    qDebug() << windowState();
    if (windowState() & Qt::WindowFullScreen) {
        setWindowState(Qt::WindowNoState);
    } else {
        setWindowState(Qt::WindowFullScreen);
    }
}

void MainWindow::setMinimumWindow()
{
    titleBar->hide();
    processBar->hide();
    setWindowState(Qt::WindowMinimized);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    setFullScreen();
}
