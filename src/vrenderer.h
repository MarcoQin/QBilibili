#ifndef VRENDERER_H
#define VRENDERER_H
#include <QtAV>
#include <QtAVWidgets>
#include <QTimer>

using namespace QtAV;

class VRenderer : public GLWidgetRenderer2
{
    Q_OBJECT
public:
    VRenderer(QWidget *parent);
    static VRenderer *instance();
    void enterDraw(QPainter &painter);
    void exitDraw(QPainter &painter);
protected:
    void paintGL();
private:
    static VRenderer *_instance;
    QTime frameTime;
    QTimer timer;
    long frameCount = 0;
private slots:
    void w_draw();
};

#endif // VRENDERER_H
