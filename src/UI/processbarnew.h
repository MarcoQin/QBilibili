#ifndef PROCESSBARNEW_H
#define PROCESSBARNEW_H
#include "floatwidget.h"
#include <QtAv>

namespace UI {

using namespace QtAV;
class ProcessBarNew : public FloatWidget
{
    Q_OBJECT
public:
    explicit ProcessBarNew(QWidget *parent);
    void setTimeOutTimer(QTimer *timer);
    void onStartPlay(qint64 startPos, qint64 stopPos);
public slots:
    void onPositionChanged(qint64 pos);
    void playerStateChanged(QtAV::AVPlayer::State state);
    void onScreenStateChanged(int state);
signals:
    void playButtonClicked();
    void sliderValueChanged(qint64 value);
    void volumeChanged(int value);
    void toggleFullScreen();
protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
private:
    QPushButton *volumeBtn;
    QPushButton *playBtn;
    QPushButton *prevBtn;
    QPushButton *nextBtn;
    QSlider *timeSlider;
    QSlider *volSlider;
    QLabel *timePass;
    QLabel *timeAll;
    QPushButton *fullScreenBtn;
    int lastVolume;
    bool mute = false;
    void setupUI();
    void connectSignals();
    QTimer *parentAutoHideTimer;
    enum PlayState{
        PlayingState = AVPlayer::State::PlayingState,
        PausedState = AVPlayer::State::PausedState,
        StoppedState = AVPlayer::State::StoppedState
    };
    void changePlayBtnBackground(PlayState state);
private slots:
    void seekBySlider(qint64 value);
    void seekBySlider(int value);
    void seekBySlider();
    void setVolumeBySlider(int);
    void setVolumeBySlider();
    void volumeBtnClicked();
};

}

#endif // PROCESSBARNEW_H
