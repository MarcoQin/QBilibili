#include "mainwindow.h"
#include "mainmenu.h"
#include "processbar.h"

using namespace UI;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    setupUI();
    processBar->setTimeOutTimer(autoHideTimer);

    connectSignals();
}

void MainWindow::setupUI()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    setAcceptDrops(true);

    mainLayout = new QGridLayout();
    mainLayout->setSizeConstraint(QLayout::SetMaximumSize);
    mainLayout->setSpacing(1);
    mainLayout->setMargin(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);

    vrenderer = new VRenderer(NULL);
    player = new AVPlayer();
    player->setRenderer(vrenderer);
    mainLayout->addWidget(vrenderer->widget(), 0, 0);

    resize(800, 600);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    processBar = new ProcessBarNew(this);
    titleBar = new TitleBar(this);
    autoHideTimer = new QTimer(this);
    autoHideTimer->setSingleShot(true);
    autoHideTimer->start(autoHideTimeOut);
}


void MainWindow::connectSignals()
{
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));
    connect(autoHideTimer, SIGNAL(timeout()), processBar, SLOT(hide()));
    connect(autoHideTimer, SIGNAL(timeout()), titleBar, SLOT(hide()));
    connect(autoHideTimer, SIGNAL(timeout()), this, SLOT(hideCursor()));

    connect(titleBar, SIGNAL(closeClicked()), this, SLOT(close()));
    connect(titleBar, SIGNAL(minClicked()), this, SLOT(setMinimumWindow()));
    connect(titleBar, SIGNAL(maxClicked()), this, SLOT(setFullScreen()));

    connect(processBar, SIGNAL(playButtonClicked()), this, SLOT(playOrPause()));
    connect(processBar, SIGNAL(sliderValueChanged(qint64)), this, SLOT(seek(qint64)));

    connect(player, SIGNAL(stateChanged(QtAV::AVPlayer::State)), processBar, SLOT(playerStateChanged(QtAV::AVPlayer::State)));
    connect(player, SIGNAL(positionChanged(qint64)), processBar, SLOT(onPositionChanged(qint64)));
    connect(player, SIGNAL(started()), this, SLOT(onStartPlay()));
}

void MainWindow::hideCursor()
{
    qDebug() << "hideCursor";
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
        // connect(fileA, &QAction::triggered, [this](){
            // QString _file = QFileDialog::getOpenFileName();
            // qDebug() << _file;
        // });
        addAction(fileA);
        connect(fileB, &QPushButton::clicked, fileA, &QAction::trigger);
    }

};

void MainWindow::ShowContextMenu(const QPoint &pos)
    {

        // qDebug()<<":popuprightclickMenu"; //just to see if activated
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
        pressPosition = event->globalPos();
        pressWidth = width();
        pressHeight = height();

        QPoint cur = event->pos();
        int x = cur.x(), y = cur.y(), w = width(), h = height();
        int lx = 0, ly = 0;
        int dx = x - lx, dy = y - ly;
        int drx = w - x, dry = h - y;
        resizeDirection = None;
        if (dry > 0 && dry < resizeMargin) {
            needResize = true;
            resizeDirection = resizeDirection | Bottom;
        }
        if (dy > 0 && dy < resizeMargin) {
            needResize = true;
            resizeDirection = resizeDirection | Top;
        }
        if (drx > 0 && drx < resizeMargin) {
            needResize = true;
            resizeDirection = resizeDirection | Right;
        }
        if (dx > 0 && dx < resizeMargin) {
            needResize = true;
            resizeDirection = resizeDirection | Left;
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
//            qDebug() << dx << dy;
            int drx = w - x, dry = h - y;
            int direct = None;
            if (dry > 0 && dry < resizeMargin) {
                direct |= Bottom;
            }
            if (dy > 0 && dy < resizeMargin) {
                direct |= Top;
            }
            if (drx > 0 && drx < resizeMargin) {
                direct |= Right;
            }
            if (dx > 0 && dx < resizeMargin) {
                direct |= Left;
            }

            switch(direct) {
            case Bottom:
                cursor = Qt::SizeVerCursor;
                break;
            case Top:
                cursor = Qt::SizeVerCursor;
                break;
            case Right:
                cursor = Qt::SizeHorCursor;
                break;
            case Left:
                cursor = Qt::SizeHorCursor;
                break;
            case Bottom | Left:
            case Top | Right:
                cursor = Qt::SizeBDiagCursor;
                break;
            case Bottom | Right:
            case Top | Left:
                cursor = Qt::SizeFDiagCursor;
                break;
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
        autoHideTimer->stop();
        if (!(cur.y() < 12 )) {
            autoHideTimer->start(autoHideTimeOut);
        }
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
            {
                move(event->globalPos().x() - dragPosition.x(), global.y());
                resize(pressWidth +  pressPosition.x() - event->globalPos().x(), h);
                break;
            }
            case Top:
            {
                move(global.x(), event->globalPos().y() - dragPosition.y());
                resize(w, pressHeight +  pressPosition.y() - event->globalPos().y());
                break;
            }
            case Left | Top:
                move(event->globalPos() - dragPosition);
                resize(pressWidth + pressPosition.x() - event->globalPos().x(), pressHeight + pressPosition.y() - event->globalPos().y());
                break;
            case Right | Top:
                move(global.x(), event->globalPos().y() - dragPosition.y());
                resize(pressWidth +  event->globalPos().x() - pressPosition.x(), pressHeight + pressPosition.y() - event->globalPos().y());
                break;
            case Left | Bottom:
                move(event->globalPos().x() - dragPosition.x(), global.y());
                resize(pressWidth + pressPosition.x() - event->globalPos().x(), pressHeight + event->globalPos().y() - pressPosition.y());
                break;
            case Right | Bottom:
                resize(pressWidth + event->globalPos().x() - pressPosition.x(), pressHeight + event->globalPos().y() - pressPosition.y());
            default:
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
    event->accept();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    titleBar->resetPosition(this);
    titleBar->resetSize(this);
    processBar->resetPosition(this);
    event->accept();
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
    event->accept();
}

AVPlayer *MainWindow::getPlayer()
{
    return player;
}

void MainWindow::playOrPause()
{
    if (!player->isPlaying()) {
        player->play();
        return;
    }
    player->pause(!player->isPaused());
}

void MainWindow::onStartPlay()
{
    processBar->onStartPlay(player->mediaStartPosition(), player->mediaStopPosition());
}

void MainWindow::seek(qint64 pos)
{
    player->setSeekType(QtAV::SeekType::AccurateSeek);
    player->seek(pos);
}
