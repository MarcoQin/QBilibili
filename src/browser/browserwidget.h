#ifndef BROWSERWIDGET_H
#define BROWSERWIDGET_H

#include "../UI/floatwidget.h"
#include <QObject>

class TabWidget;

namespace UI {

class BrowserWidget : public FloatWidget
{
    Q_OBJECT
public:
    explicit BrowserWidget(QWidget *parent);
    void resetSize(QWidget *parent);

    TabWidget *tabWidget() const;

    void loadPage(const QString &url);
    void loadPage(const QUrl &url);
    void loadHomePage();
private:
    void setupUI();
    int titleOffset = 20;
    TabWidget *m_tabWidget;
};

}
#endif // BROWSERWIDGET_H
