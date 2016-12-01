#include "mainwindow.h"
#include "mainmenu.h"
#include "processbar.h"
#include "processbarnew.h"

using namespace UI;

class Test1 : public QWidget
{
public:
    Test1(QWidget *parent) :
        QWidget(parent)
    {
//        setAutoFillBackground(true);
//        QPalette palette = this->palette();
//        palette.setColor(QPalette::Window, Qt::white);
//        this->setPalette(palette);
//        219, 199, 188
//        setWindowFlags(Qt::Popup);
//        setWindowFlags(Qt::WindowStaysOnTopHint);
        setMouseTracking(true);
        setObjectName(QString("haha"));
        setWindowFlags(
                       Qt::Tool |
                       Qt::FramelessWindowHint|
                       Qt::WindowStaysOnTopHint |
                    Qt::X11BypassWindowManagerHint |
                    Qt::NoDropShadowWindowHint|
                    Qt::WindowSystemMenuHint|
                        Qt::SubWindow);
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
        setAttribute(Qt::WA_TranslucentBackground, true);
        setStyleSheet("QWidget#haha{background:rgba(100, 96, 87, 70%);}QLabel{color:rgba(219, 199, 188, 100%);}QPushButton{background:rgba(0, 0, 0, 0%);}");
//        setStyleSheet("QWidget#haha{background:rgba(100, 96, 87, 100%);}");
//        show();
    }

protected:
    void paintEvent(QPaintEvent* /*event*/) {
     QColor backgroundColor = QColor(100, 96, 87);
     backgroundColor.setAlpha(200);
     QPainter customPainter(this);
     customPainter.fillRect(rect(),backgroundColor);
    }

};

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{
    setMouseTracking(true);
    setAcceptDrops(true);
    resize(800, 600);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
//    Test1 *t = new Test1(this);
//    t->show();
    ProcessBarNew *b = new ProcessBarNew(this);
    b->show();
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

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{

//    qDebug() << "MainWindow Pos: ";
//    qDebug() << pos();
//    qDebug() << "MapToGlobalPos: ";
//    qDebug() << mapToGlobal(pos());
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
