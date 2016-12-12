#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QObject>
#include <QWidget>

class ContextMenu : public QWidget
{
    Q_OBJECT
public:
    explicit ContextMenu(QWidget *parent = 0);

signals:

public slots:
};

#endif // CONTEXTMENU_H