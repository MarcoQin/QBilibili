#ifndef TABWIDGET_H
#define TABWIDGET_H


#include <QTabWidget>
#include <QWebEnginePage>

QT_BEGIN_NAMESPACE
class QUrl;
QT_END_NAMESPACE

class WebView;


class TabWidget : public QTabWidget
{
public:
    TabWidget(QWidget *parent = nullptr);

    WebView *currentWebView() const;
signals:
//    void iconChanged(const QIcon &icon);
//    void titleChanged(const QString &title);
//    void urlChanged(const QUrl &url);
public slots:
    void setUrl(const QUrl &url);
    WebView *createTab(bool makeCurrent = true);
    void closeTab(int index);
    void handleCurrentChanged(int index);
private:
    WebView *webView(int index) const;
    void setupView(WebView *webView);
};

#endif // TABWIDGET_H
