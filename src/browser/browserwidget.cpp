#include "browserwidget.h"
#include "tabwidget.h"
#include "webview.h"

using namespace UI;

BrowserWidget::BrowserWidget(QWidget *parent) :
    FloatWidget(parent)
//    QWidget(parent)
{
    setupUI();
    setMouseTracking(true);

    m_tabWidget->createTab();
}


void BrowserWidget::setupUI()
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetMaximumSize);
    mainLayout->setSpacing(1);
    mainLayout->setMargin(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    m_tabWidget = new TabWidget();
    mainLayout->addWidget(m_tabWidget, 0, 0);
    setLayout(mainLayout);
    setPosition(Center);
    setCustomPositionOffset(QPoint(0, titleOffset / 2));
}

TabWidget *BrowserWidget::tabWidget() const
{
    return m_tabWidget;
}


void BrowserWidget::resetSize(QWidget *parent)
{
    resize(parent->width() - 8, parent->height() - titleOffset - 4);
}

void BrowserWidget::loadPage(const QString &url)
{
    loadPage(QUrl::fromUserInput(url));
}

void BrowserWidget::loadPage(const QUrl &url)
{
    if (url.isValid()) {
        m_tabWidget->setUrl(url);
    }
}

void BrowserWidget::loadHomePage()
{
    loadPage("http://www.bilibili.com");
}
