#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QIcon>
#include <QWebEngineView>


class WebView : public QWebEngineView
{
    Q_OBJECT
public:
    WebView(QWidget *parent = nullptr);
    QIcon icon() const;

    static QNetworkAccessManager &networkAccessManager();

signals:
    void iconChanged(const QIcon &icon);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType type) override;
private slots:
    void handleIconUrlChanged(const QUrl &url);
    void handleIconLoaded();

private:
    QIcon m_icon;
};

#endif // WEBVIEW_H
