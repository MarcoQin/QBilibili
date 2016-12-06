#include "processbarnew.h"
using namespace UI;

ProcessBarNew::ProcessBarNew(QWidget *parent) :
    FloatWidget(parent)
{
    setupUI();
    // int dark = 20;
    // setBackgroundColor(QColor(100 - dark, 96 - dark, 87 - dark));
    setBackgroundColor(QColor(42, 42, 42));
    setBackgroundAlpha(0.8f);
    setPosition(BottomCenter);
    setCustomPositionOffset(QPoint(0, -40));

    connectSignals();
}


void ProcessBarNew::setupUI()
{
    volume = new QPushButton(this);
    volume->setStyleSheet("border-image:url(:/Picture/vol_high.png)");

    prev = new QPushButton(this);
    prev->setStyleSheet("border-image:url(:/Picture/prev_episode.png);");
    play = new QPushButton(this);
    play->setStyleSheet("border-image:url(:/Picture/b_play.png);");
    next = new QPushButton(this);
    next->setStyleSheet("border-image:url(:/Picture/next_episode.png);");

    fullScreen = new QPushButton(this);
    fullScreen->setStyleSheet("border-image:url(:/Picture/enterfullscreen.png);");

    timeSlider = new QSlider(this);
    timeSlider->setOrientation(Qt::Horizontal);
    QFile f(":/qss/slider.qss");
    if (!f.exists()) {
        qDebug() << "slider.qss not exists!!";
    } else {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        timeSlider->setStyleSheet(ts.readAll());
        f.close();
    }

    volSlider = new QSlider(this);
    volSlider->setOrientation(Qt::Horizontal);
    QFile f1(":/qss/vol_slider.qss");
    if (!f1.exists()) {
        qDebug() << "vol_slider.qss not exists!!";
    } else {
        f1.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts1(&f1);
        volSlider->setStyleSheet(ts1.readAll());
        f1.close();
    }

    QString labelStyle = "QLabel{color:rgba(219, 199, 188, 100%)}";
    timePass = new QLabel(this);
    timePass->setStyleSheet(labelStyle);
    timePass->setText(" 00:00");
    timeAll = new QLabel(this);
    timeAll->setStyleSheet(labelStyle);
    timeAll->setText(" 00:00");


    // new stuffs
    resize(440, 64);
    volume->setGeometry(9, 15, 16, 16);
    prev->setGeometry(160, 13, 24, 24);
    play->setGeometry(210, 13, 24, 24);
    next->setGeometry(256, 13, 24, 24);
    fullScreen->setGeometry(400, 13, 20, 20);
    timeSlider->setGeometry(63, 40, 314, 17);
    volSlider->setGeometry(32, 15, 80, 17);
    timePass->setGeometry(4, 40, 57, 14);
    timeAll->setGeometry(381, 40, 57, 14);
}

void ProcessBarNew::connectSignals()
{
    connect(play, SIGNAL(clicked(bool)), this, SIGNAL(playButtonClicked()));
    connect(timeSlider, SIGNAL(sliderPressed()), this, SLOT(seekBySlider()));
    connect(timeSlider, SIGNAL(sliderMoved(int)), this, SLOT(seekBySlider(int)));
}

void ProcessBarNew::mouseMoveEvent(QMouseEvent *event)
{
    parentAutoHideTimer->stop();
    event->accept();
}

void ProcessBarNew::setTimeOutTimer(QTimer *timer)
{
    parentAutoHideTimer = timer;
}

void ProcessBarNew::changePlayBtnBackground(PlayState state)
{
    switch(state) {
        case PlayingState:
            play->setStyleSheet("border-image:url(:/Picture/pause.png);");
            break;
        case PausedState:
        case StoppedState:
            play->setStyleSheet("border-image:url(:/Picture/b_play.png);");
            break;
    }
}


void ProcessBarNew::playerStateChanged(QtAV::AVPlayer::State state)
{
    qDebug() << "playerStateChanged";
    changePlayBtnBackground((PlayState)state);
    switch(state) {
        case PlayingState:
            break;
        case PausedState:
            break;
        case StoppedState:
            break;
    }
}

void ProcessBarNew::onPositionChanged(qint64 pos)
{
    timeSlider->setValue(pos);
    timePass->setText(QTime(0, 0, 0).addMSecs(pos).toString("HH:mm:ss"));
}

void ProcessBarNew::onStartPlay(qint64 startPos, qint64 stopPos)
{
    timeSlider->setMinimum(startPos);
    timeSlider->setMaximum(stopPos);
    timeSlider->setValue(0);
    timeAll->setText(QTime(0, 0, 0).addMSecs(stopPos).toString("HH:mm:ss"));
}

void ProcessBarNew::seekBySlider(qint64 value)
{
    emit sliderValueChanged(value);
}

void ProcessBarNew::seekBySlider()
{
    emit sliderValueChanged((qint64)timeSlider->value());
}

void ProcessBarNew::seekBySlider(int value)
{
    emit sliderValueChanged((qint64)value);
}
