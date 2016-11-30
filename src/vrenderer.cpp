#include "vrenderer.h"

#include <Qt>
#include <QtWidgets>

class Test : public QWidget
{
public:
    Test(QWidget *parent) :
        QWidget(parent)
    {
//        setAutoFillBackground(true);
//        QPalette palette = this->palette();
//        palette.setColor(QPalette::Window, Qt::white);
//        this->setPalette(palette);
//        219, 199, 188
//        setWindowFlags(Qt::Popup);
//        setWindowFlags(Qt::WindowStaysOnTopHint);
        setObjectName(QString("haha"));
        setWindowFlags(
                       Qt::Tool |
                       Qt::FramelessWindowHint|
                       Qt::WindowStaysOnTopHint |
                    Qt::X11BypassWindowManagerHint |
                    Qt::NoDropShadowWindowHint|
                    Qt::WindowSystemMenuHint|
                        Qt::SubWindow);
        QHBoxLayout* pLayout = new QHBoxLayout();
        QLabel *pLabel = new QLabel ("title");
        pLayout->addWidget (pLabel);
        QSpinBox *pSpinBox = new QSpinBox(NULL);
        pLayout->addWidget (pSpinBox);
        setLayout (pLayout);
        QLabel *timeT = new QLabel(tr("Time"), this);
        QLabel *volmT = new QLabel(tr("Volume"), this);
        QSlider *timeS = new QSlider(this);
        QSlider *volmS = new QSlider(this);
        timeS->setOrientation(Qt::Horizontal);
        volmS->setOrientation(Qt::Horizontal);
        timeS->setRange(0, 0);
        volmS->setRange(0, 100);
        timeS->setValue(0);
        pLayout->addWidget(timeT);
        pLayout->addWidget(volmT);
        pLayout->addWidget(volmS);
        pLayout->addWidget(timeS);
        QPushButton *fileB = new QPushButton(this);
        fileB->setText(tr("Open"));
        pLayout->addWidget(fileB);
        QAction *fileA = new QAction(tr("Open File"), this);
        fileA->setObjectName("File");
        connect(fileA, &QAction::triggered, [this](){
            QString _file = QFileDialog::getOpenFileName();
            qDebug() << _file;
        });
        addAction(fileA);
        connect(fileB, &QPushButton::clicked, fileA, &QAction::trigger);
        setAttribute(Qt::WA_TranslucentBackground, true);
        setStyleSheet("QWidget#haha{background:rgba(100, 96, 87, 70%);}QLabel{color:rgba(219, 199, 188, 100%);}QPushButton{background:rgba(0, 0, 0, 0%);}");
//        setStyleSheet("QWidget#haha{background:rgba(100, 96, 87, 100%);}");
//        show();
    }

protected:
    void paintEvent(QPaintEvent* /*event*/) {
     QColor backgroundColor = QColor(100, 96, 87);
     backgroundColor.setAlpha(200);
     QPainter customPainter(this);
     customPainter.fillRect(rect(),backgroundColor);
    }

};
VRenderer::VRenderer(QWidget *parent)
    :GLWidgetRenderer2(parent)
{
    setMouseTracking(true);
//    Test *t = new Test(parent);
//    t->show();
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

