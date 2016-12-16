#ifndef TESTWIDGET_H
#define TESTWIDGET_H
#include <Qt>
#include <QtWidgets>

#include "processbarnew.h"
#include "titlebar.h"
#include "../vrenderer.h"
#include "mainmenu.h"
#include "contextmenu.h"

namespace UI {

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent);
    static constexpr int None = 0x00000000;
    static constexpr int Left = 0x00000001;
    static constexpr int Top = 0x00000002;
    static constexpr int Right = 0x00000004;
    static constexpr int Bottom = 0x00000008;
    AVPlayer *getPlayer();
signals:
    void fullscreenStateChanged(int state);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void moveEvent(QMoveEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void setupUI();
    virtual void showEvent(QShowEvent *event);
private:
    bool playerUsing = false;  // if file loaded, this value will be true;
    ContextMenu *contextMenu;
    void connectSignals();
    QGridLayout *mainLayout;
    VRenderer *vrenderer;
    AVPlayer *player;
    SubtitleFilter *subtitleEngine;
    QPoint dragPosition;
    QPoint pressPosition;
    int pressWidth;
    int pressHeight;
    QTimer *autoHideTimer;
    int autoHideTimeOut = 1500;
    TitleBar *titleBar;
    ProcessBarNew *processBar;
    MainMenu *mainMenu;
    bool needResize = false;
    int resizeDirection = None;
    int resizeMargin = 5;
    QCursor cursor = Qt::ArrowCursor;
    int videoWidth, videoHeight;
    bool scaleByRatio = true;
    int minWindowWidth = 600;
    int minWindowHeight = 400;
    qreal aspectRatio;
    bool autoPlay = true;
private slots:
    void ShowContextMenu(const QPoint &pos);
    void hideCursor();
    void showCursor(QCursor &cursor);
    void toggleFullScreen();
    void setMinimumWindow();
    void playOrPause();
    void onStartPlay();
    void seek(qint64 pos);
    void setVolume(int value);
    void fileLoaded();
    void openNewFile(QString fileName);
    void stopAutoHideTimer();
    void maxmizeWindow();
};

}
#endif // TESTWIDGET_H
