#include "vrenderer.h"
#include "lua/luamanager.h"

#include <Qt>
#include <QtWidgets>

VRenderer* VRenderer::_instance = nullptr;

VRenderer::VRenderer(QWidget *parent)
    :GLWidgetRenderer2(parent)
{
    setMouseTracking(true);
    setGeometry(0, 0, 800, 600);
    frameTime.start();
    // connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(w_draw()));
    timer.setInterval(17);
    timer.start();
    _instance = this;
}

VRenderer *VRenderer::instance()
{
    return _instance ? _instance : new VRenderer(NULL);
}

void VRenderer::paintGL()
{
    // default draw function
    // make if empty
    // to ensure w_draw will be called correctly
}

void VRenderer::enterDraw(QPainter &painter)
{
    painter.beginNativePainting();
    handlePaintEvent();
}

void VRenderer::exitDraw(QPainter &painter)
{
    painter.endNativePainting();
    swapBuffers();
}

void VRenderer::w_draw()
{
    // ++frameCount;
//    double fps = frameCount / ((double)frameTime.elapsed() / 1000.0);
    double dt = ((double)frameTime.elapsed() - lastFrameTiem )/ 1000.0;
    lastFrameTiem = frameTime.elapsed();
    QPainter painter(this);
    enterDraw(painter);

    LuaManager::instance()->callUpdateFunc(dt);
    LuaManager::instance()->callDrawFunc(painter);

    exitDraw(painter);
}
