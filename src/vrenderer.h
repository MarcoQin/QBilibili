#ifndef VRENDERER_H
#define VRENDERER_H
#include <QtAV>
#include <QtAVWidgets>
#include <QTimer>

using namespace QtAV;

class VRenderer : public GLWidgetRenderer2
{
public:
    VRenderer(QWidget *parent);
protected:
    void paintGL();
private:
    QTime frameTime;
    QTimer timer;
    long frameCount = 0;
};

#endif // VRENDERER_H
