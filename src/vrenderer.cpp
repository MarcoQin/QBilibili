#include "vrenderer.h"

#include <Qt>
#include <QtWidgets>

VRenderer::VRenderer(QWidget *parent)
    :GLWidgetRenderer2(parent)
{

    setGeometry(0, 0, 800, 600);

}

void VRenderer::paintGL()
{
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


    // leave draw context
    painter.endNativePainting();

    // swap gl buffer
    swapBuffers();
}

