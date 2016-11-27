#ifndef VRENDERER_H
#define VRENDERER_H
#include <QtAV>
#include <QtAVWidgets>

using namespace QtAV;

class VRenderer : public GLWidgetRenderer2
{
public:
    VRenderer(QWidget *parent);
protected:
    void paintGL();
public slots:
    void ShowContextMenu(const QPoint &pos);
};

#endif // VRENDERER_H
