#ifndef VRENDERER_H
#define VRENDERER_H
#include <QtAV>
#include <QtAVWidgets>

using namespace QtAV;

class VRenderer : public GLWidgetRenderer2
{
public:
    VRenderer();
protected:
    void paintGL();
};

#endif // VRENDERER_H
