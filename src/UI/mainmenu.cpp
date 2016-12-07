#include "mainmenu.h"

using namespace UI;

MainMenu::MainMenu(QWidget *parent) :
    FloatWidget(parent)
{
    setMouseTracking(true);
    setupUI();
    setBackgroundColor(QColor(42, 42, 42));
    setBackgroundAlpha(0.8f);
    setPosition(Center);

    connectSignals();
}

void MainMenu::setupUI()
{
    resize(200, 200);

    QString commonButtonStyle;
    QFile f(":/qss/common_button.qss");
    if (!f.exists()) {
        qDebug() << "common_button.qss not exists!!";
    } else {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts1(&f);
        commonButtonStyle = ts1.readAll();
        f.close();
    }

    openBtn = new QPushButton(this);
    openBtn->setStyleSheet(commonButtonStyle);
    openBtn->setGeometry(20, 50, 74, 32);
    openBtn->setText(tr("Open"));

    openURL = new QPushButton(this);
    openURL ->setStyleSheet(commonButtonStyle);
    openURL ->setGeometry(114, 50, 74, 32);
    openURL ->setText(tr("Open URL"));
}

void MainMenu::connectSignals()
{
    connect(openBtn, SIGNAL(clicked(bool)), this, SLOT(openFile()));
}

// slots
void MainMenu::openFile()
{
    QString _fileName = QFileDialog::getOpenFileName();
    if (_fileName.isEmpty()) {
        return;
    }
    emit newFileOpened(_fileName);
    hide();
}

void MainMenu::mouseMoveEvent(QMouseEvent *event)
{
    emit stopTimer();
    event->accept();
}
