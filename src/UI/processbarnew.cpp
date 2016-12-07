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
    volumeBtn = new QPushButton(this);
    volumeBtn->setStyleSheet("border-image:url(:/Picture/vol_high.png)");

    prevBtn = new QPushButton(this);
    prevBtn->setStyleSheet("border-image:url(:/Picture/prev_episode.png);");
    playBtn = new QPushButton(this);
    playBtn->setStyleSheet("border-image:url(:/Picture/b_play.png);");
    nextBtn = new QPushButton(this);
    nextBtn->setStyleSheet("border-image:url(:/Picture/next_episode.png);");

    fullScreenBtn = new QPushButton(this);
    fullScreenBtn->setStyleSheet("border-image:url(:/Picture/enterfullscreen.png);");

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
    volSlider->setMaximum(100);
    volSlider->setValue(100);
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
    volumeBtn->setGeometry(9, 15, 16, 16);
    prevBtn->setGeometry(160, 13, 24, 24);
    playBtn->setGeometry(210, 13, 24, 24);
    nextBtn->setGeometry(256, 13, 24, 24);
    fullScreenBtn->setGeometry(400, 13, 20, 20);
    timeSlider->setGeometry(63, 40, 314, 17);
    volSlider->setGeometry(32, 15, 80, 17);
    timePass->setGeometry(4, 40, 57, 14);
    timeAll->setGeometry(381, 40, 57, 14);
}

void ProcessBarNew::connectSignals()
{
    connect(playBtn, SIGNAL(clicked(bool)), this, SIGNAL(playButtonClicked()));

    connect(timeSlider, SIGNAL(sliderPressed()), this, SLOT(seekBySlider()));
    connect(timeSlider, SIGNAL(sliderMoved(int)), this, SLOT(seekBySlider(int)));

    connect(volumeBtn, SIGNAL(clicked(bool)), this, SLOT(volumeBtnClicked()));
    connect(volSlider, SIGNAL(sliderPressed()), this, SLOT(setVolumeBySlider()));
    connect(volSlider, SIGNAL(sliderMoved(int)), this, SLOT(setVolumeBySlider(int)));

    connect(fullScreenBtn, SIGNAL(clicked(bool)), this, SIGNAL(toggleFullScreen()));
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
            playBtn->setStyleSheet("border-image:url(:/Picture/pause.png);");
            break;
        case PausedState:
        case StoppedState:
            playBtn->setStyleSheet("border-image:url(:/Picture/b_play.png);");
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

    setVolumeBySlider(volSlider->value());
}

void ProcessBarNew::seekBySlider(qint64 value)
{
    emit sliderValueChanged(value);
}

void ProcessBarNew::seekBySlider()
{
    seekBySlider((qint64)timeSlider->value());
}

void ProcessBarNew::seekBySlider(int value)
{
    seekBySlider((qint64)value);
}

void ProcessBarNew::setVolumeBySlider(int value)
{
    emit volumeChanged(value);
    if (value <= 0) {
        if (mute) {
            volumeBtn->setStyleSheet("border-image:url(:/Picture/mute.png)");
        } else {
            volumeBtn->setStyleSheet("border-image:url(:/Picture/vol_no.png)");
        }
    } else if (value > 0 && value <= 33) {
        volumeBtn->setStyleSheet("border-image:url(:/Picture/vol_low.png)");
    } else if (value > 33 && value <= 66) {
        volumeBtn->setStyleSheet("border-image:url(:/Picture/vol_mid.png)");
    } else {
        volumeBtn->setStyleSheet("border-image:url(:/Picture/vol_high.png)");
    }
}
void ProcessBarNew::setVolumeBySlider()
{
    setVolumeBySlider(volSlider->value());
}

void ProcessBarNew::volumeBtnClicked()
{
    mute = !mute;
    if (mute) {
        lastVolume = volSlider->value();
        volSlider->setValue(0);
        setVolumeBySlider(0);
    } else {
        setVolumeBySlider(lastVolume);
        volSlider->setValue(lastVolume);
    }
}

void ProcessBarNew::onScreenStateChanged(int state)
{
    switch(state) {
        case 0:
            fullScreenBtn->setStyleSheet("border-image:url(:/Picture/enterfullscreen.png);");
            break;
        case 1:
            fullScreenBtn->setStyleSheet("border-image:url(:/Picture/exitfullscreen.png);");
            break;
    }
}
