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
    if (1 < 2) {
        return;
    }
    ++frameCount;
    double fps = frameCount / ((double)frameTime.elapsed() / 1000.0);
    // mix gl and qpainter
    QPainter painter(this);
    // enter draw context
    painter.beginNativePainting();

    // video draw stuffs
    handlePaintEvent();

    // custom draw stuffs
    // ---- draw normal text
    int alpha = 100;
    painter.setPen(QColor(100, 100, 200, 255));
    QFont font;
    font.setPixelSize(24);
    painter.setFont(font);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.drawText(10, 10, "Hello World");
    painter.drawLine(0, 0, 400, 400);
    painter.drawText(100, 100, "你好世界");
    // ---- draw text with outline
    QPainterPath path;
    QPen pen;
    QPoint posToDraw(50, 132);
    font.setWeight(QFont::Weight::Normal);
    pen.setWidth(5);
    pen.setColor(QColor(0, 0, 0, alpha));
    painter.setFont(font);
    painter.setPen(pen);

    const QString textToDraw("中文And English with Σ(*ﾟдﾟﾉ)ﾉ...");
    path.addText(posToDraw,font, textToDraw);
    painter.drawPath(path);
    pen.setColor(QColor(255, 255, 255, alpha));
    painter.setPen(pen);
    painter.drawText(posToDraw, textToDraw);


    QFontMetrics fm(font);
    int pixelsWide = fm.width(textToDraw);
    int piexelsHigh = fm.height();
    // qDebug() << pixelsWide << piexelsHigh;
    // qDebug() << width() ;

    painter.drawText(QPoint(300, 100), QString::number(fps));
//    painter.drawText(QPoint(350, 100), QString::number(frameCount));
//    painter.drawText(QPoint(400, 100), QString::number(frameTime.elapsed()));

    // leave draw context
    painter.endNativePainting();

    // swap gl buffer
    swapBuffers();
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
    ++frameCount;
    double fps = frameCount / ((double)frameTime.elapsed() / 1000.0);
    // mix gl and qpainter
    QPainter painter(this);
    enterDraw(painter);
    // enter draw context
    // painter.beginNativePainting();

    // video draw stuffs
    // handlePaintEvent();

    // custom draw stuffs
    // ---- draw normal text
//    int alpha = 100;
//    painter.setPen(QColor(100, 100, 200, 255));
//    QFont font;
//    font.setPixelSize(24);
//    painter.setFont(font);
//    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//    painter.drawText(10, 10, "Hello World");
//    painter.drawLine(0, 0, 400, 400);
//    painter.drawText(100, 100, "你好世界");
//    // ---- draw text with outline
//    QPainterPath path;
//    QPen pen;
//    QPoint posToDraw(50, 132);
//    font.setWeight(QFont::Weight::Normal);
//    pen.setWidth(5);
//    pen.setColor(QColor(0, 0, 0, alpha));
//    painter.setFont(font);
//    painter.setPen(pen);

//    const QString textToDraw("中文And English with Σ(*ﾟдﾟﾉ)ﾉ...");
//    path.addText(posToDraw,font, textToDraw);
//    painter.drawPath(path);
//    pen.setColor(QColor(255, 255, 255, alpha));
//    painter.setPen(pen);
//    painter.drawText(posToDraw, textToDraw);


//    QFontMetrics fm(font);
//    int pixelsWide = fm.width(textToDraw);
//    int piexelsHigh = fm.height();
    // qDebug() << pixelsWide << piexelsHigh;
    // qDebug() << width() ;

    LuaManager::instance()->callDrawFunc(painter);

//    painter.drawText(QPoint(30, 50), QString::number(int(fps)) + " FPS");
//    painter.drawText(QPoint(350, 100), QString::number(frameCount));
//    painter.drawText(QPoint(400, 100), QString::number(frameTime.elapsed()));

    // leave draw context
    // painter.endNativePainting();

    // swap gl buffer
    // swapBuffers();
    exitDraw(painter);
}
