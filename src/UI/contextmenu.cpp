#include "contextmenu.h"
#include <string>
#include <sstream>
#include <iostream>
#include "../lua/luamanager.h"

using namespace UI;

ContextMenu::ContextMenu(QWidget *parent) :
    QMenu(parent)
{
    setupUI();
    connectSignals();
}

void ContextMenu::setupUI()
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("QMenu{background:rgba(100, 96, 87, 70%);}QLabel{color:rgba(219, 199, 188, 100%);}");

    openMenu = new QMenu("Open", this);
    open = new QAction("Open File", this);
    openMenu->addAction(open);
    openURL = new QAction("Open URL", this);
    openMenu->addAction(openURL);
    this->addMenu(openMenu);
    stop = new QAction("Stop", this);
    this->addAction(stop);

    // showBrowser = new QAction("ShowBrowser", this);
    // this->addAction(showBrowser);

    urlDialog = new URLDialog();
}

void ContextMenu::connectSignals()
{
    connect(open, SIGNAL(triggered()), this, SLOT(openFile()));

    connect(stop, SIGNAL(triggered()), this, SIGNAL(stopClicked()));

    connect(openURL, SIGNAL(triggered()), this, SLOT(openURLClicked()));
    connect(urlDialog, SIGNAL(URLOpened(QString)), this, SIGNAL(fileOrURLOpened(QString)));

    // connect(showBrowser, SIGNAL(triggered(bool)), this, SIGNAL(showWebBrowser()));
}

void ContextMenu::openFile()
{
    QString _fileName = QFileDialog::getOpenFileName();
    if (_fileName.isEmpty()) {
        return;
    }
    emit fileOrURLOpened(_fileName);
}

URLDialog::URLDialog()
{
    resize(400, 180);
    setMouseTracking(true);
    setWindowFlags(
                   Qt::FramelessWindowHint
                   );
    backgroundMask = new QFrame(this);
    backgroundMask->setMouseTracking(true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    QLabel *label = new QLabel(this);
    label->setStyleSheet("background-color: rgba(0, 0, 0, 0%);color: rgba(219, 199, 188, 100%);");
    label->setText("Type URL:");
    label->setGeometry(50, 20, 100, 20);
    url = new QLineEdit(this);
    url->setGeometry(50, 50, 300, 50);
    QPushButton *ok = new QPushButton("ok", this);
    ok->setGeometry(50, 120, 64, 32);
    QPushButton *cancel = new QPushButton("cancel", this);
    cancel->setGeometry(318 - 32, 120, 64, 32);
    QColor color(100, 96, 87, 200);

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
    ok->setStyleSheet(commonButtonStyle);
    cancel->setStyleSheet(commonButtonStyle);


    QString lineEditStyle;
    QFile f1(":/qss/line_edit.qss");
    if (!f.exists()) {
        qDebug() << "line_edit.qss not exists!!";
    } else {
        f1.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts1(&f1);
        lineEditStyle = ts1.readAll();
        f1.close();
    }
    url->setStyleSheet(lineEditStyle);
    url->setAttribute(Qt::WA_MacShowFocusRect, 0);

    std::stringstream styleStream;
    int r, g, b, a;
    color.getRgb(&r, &g, &b, &a);
    styleStream << "QFrame{background:rgba("
          << r << ","
          << g << ","
          << b << ","
          << a * 100 / 255 << "%);"
          << "border-radius:" << 10 << "px;"
          << "}";
    std::string style = styleStream.str();
    backgroundMask->setStyleSheet(style.c_str());

    connect(cancel, SIGNAL(clicked(bool)), this, SLOT(hide()));
    connect(ok, SIGNAL(clicked(bool)), this, SLOT(okBtnClicked()));

}

void URLDialog::showEvent(QShowEvent *){
    backgroundMask->resize(width(), height());
}

void URLDialog::okBtnClicked()
{
    QString s = url->text();
    if (!s.isEmpty()) {
        qDebug() << s;
        const char *u = LuaManager::instance()->callGetAdressFunc(s, 1);
        qDebug() << "here";
        qDebug() << u;
        emit URLOpened(u);
    }
    hide();
}

void ContextMenu::openURLClicked()
{
    urlDialog->exec();
}


