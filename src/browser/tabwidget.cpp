#include "tabwidget.h"
#include "webview.h"
#include "webpage.h"
#include <QMenu>
#include <QTabBar>
#include <QWebEngineProfile>
#include <QFile>

TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    QTabBar *tabBar = this->tabBar();
    tabBar->setTabsClosable(true);
    tabBar->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
    tabBar->setMovable(true);
    tabBar->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tabBar, &QTabBar::tabCloseRequested, this, &TabWidget::closeTab);

    connect(this, &QTabWidget::currentChanged, this, &TabWidget::handleCurrentChanged);

    setDocumentMode(true);
    setElideMode(Qt::ElideRight);

    QFile f(":/qss/tabbar.qss");
    if (!f.exists()) {
        qDebug() << "tabbar.qss not exists!!";
    } else {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        QString s = ts.readAll();
        setStyleSheet(s);
        f.close();
    }
}

void TabWidget::handleCurrentChanged(int index)
{
    if (index != -1) {
        WebView *view = webView(index);
        if (!view->url().isEmpty())
            view->setFocus();
//        emit titleChanged(view->title());
//        emit urlChanged(view->url());
//        emit iconChanged(view->icon());
    } else {
//        emit titleChanged(QString());
//        emit urlChanged(QUrl());
//        emit iconChanged(QIcon());
    }
}

WebView *TabWidget::createTab(bool makeCurrent)
{
    WebView *webView = new WebView;
    WebPage *webPage = new WebPage(QWebEngineProfile::defaultProfile(), webView);
    webView->setPage(webPage);
    setupView(webView);

    addTab(webView, tr("Untitled"));
    if (makeCurrent){
        setCurrentWidget(webView);
    }
    return webView;
}

WebView *TabWidget::currentWebView() const
{
    return webView(currentIndex());
}

WebView *TabWidget::webView(int index) const
{
    return qobject_cast<WebView*>(widget(index));
}


void TabWidget::setUrl(const QUrl &url)
{
    if (WebView *view = currentWebView()) {
        view->setUrl(url);
        view->setFocus();
    }
}

void TabWidget::closeTab(int index)
{
    qDebug() << "closeTab";
    if (WebView *view = webView(index)) {
        bool hasFocus = view->hasFocus();
        removeTab(index);
        if (hasFocus && count() > 0)
            currentWebView()->setFocus();
        if (count() == 0)
            createTab();
        view->deleteLater();
    }
}


void TabWidget::setupView(WebView *webView)
{
    QWebEnginePage *webPage = webView->page();

    connect(webView, &QWebEngineView::titleChanged, [this, webView](const QString &title) {
        int index = indexOf(webView);
        if (index != -1) {
            setTabText(index, title);
        }
    });
    connect(webView, &WebView::iconChanged, [this, webView](const QIcon& icon) {
        int index = indexOf(webView);
        if (index != -1)
            setTabIcon(index, icon);
    });
    connect(webPage, &QWebEnginePage::windowCloseRequested, [this, webView]() {
        int index = indexOf(webView);
        if (index >= 0)
            closeTab(index);
    });
}
