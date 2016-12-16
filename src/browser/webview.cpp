#include "webview.h"
#include "browserwidget.h"
#include "tabwidget.h"
#include <QMenu>
#include <QMessageBox>
#include <QNetworkReply>
#include <QTimer>

using namespace UI;

WebView::WebView(QWidget *parent):
    QWebEngineView(parent)
{
    connect(this, &QWebEngineView::iconUrlChanged, this, &WebView::handleIconUrlChanged);
}

QWebEngineView *WebView::createWindow(QWebEnginePage::WebWindowType type)
{
    BrowserWidget *mainWidget = qobject_cast<BrowserWidget*>(window());
    return mainWidget->tabWidget()->createTab();
}


void WebView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = page()->createStandardContextMenu();
    const QList<QAction*> actions = menu->actions();
    auto it = std::find(actions.cbegin(), actions.cend(), page()->action(QWebEnginePage::OpenLinkInThisWindow));
    if (it != actions.cend()) {
        (*it)->setText(tr("Open Link in This Tab"));
        ++it;
        QAction *before(it == actions.cend() ? nullptr : *it);
//        menu->insertAction(before, page()->action(QWebEnginePage::OpenLinkInNewWindow));
        menu->insertAction(before, page()->action(QWebEnginePage::OpenLinkInNewTab));
    }
    connect(menu, &QMenu::aboutToHide, menu, &QObject::deleteLater);
    menu->popup(event->globalPos());
}

QIcon WebView::icon() const
{
    if (!m_icon.isNull())
        return m_icon;
    return QIcon();
}

QNetworkAccessManager &WebView::networkAccessManager()
{
    static QNetworkAccessManager networkAccessManager;
    return networkAccessManager;
}


void WebView::handleIconUrlChanged(const QUrl &url)
{
    QNetworkRequest iconRequest(url);
#ifndef QT_NO_OPENSSL
    QSslConfiguration conf = iconRequest.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    iconRequest.setSslConfiguration(conf);
#endif
    QNetworkReply *iconReply = networkAccessManager().get(iconRequest);
    iconReply->setParent(this);
    connect(iconReply, &QNetworkReply::finished, this, &WebView::handleIconLoaded);
}

void WebView::handleIconLoaded()
{
    QNetworkReply *iconReply = qobject_cast<QNetworkReply*>(sender());
    if (iconReply && iconReply->error() == QNetworkReply::NoError) {
        QByteArray data = iconReply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(data);
        m_icon.addPixmap(pixmap);
        iconReply->deleteLater();
    } else {
        m_icon = QIcon(QStringLiteral(":defaulticon.png"));
    }
    emit iconChanged(m_icon);
}
