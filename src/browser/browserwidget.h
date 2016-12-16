#ifndef BROWSERWIDGET_H
#define BROWSERWIDGET_H

#include "../UI/floatwidget.h"
#include <QObject>

namespace UI {

class BrowserWidget : public FloatWidget
{
    Q_OBJECT
public:
    explicit BrowserWidget(QWidget *parent);
    void resetSize(QWidget *parent);
private:
    void setupUI();
    int titleOffset = -20;
};

}
#endif // BROWSERWIDGET_H
