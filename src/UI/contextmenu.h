#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QtWidgets>
#include <QObject>
#include <QMenu>

namespace UI {

class URLDialog : public QDialog
{
    Q_OBJECT
public:
    URLDialog();
signals:
    void URLOpened(QString fileName);
protected:
    virtual void showEvent(QShowEvent *);
private:
    QFrame *backgroundMask;
    QLineEdit *url;
private slots:
    void okBtnClicked();
};

class ContextMenu : public QMenu
{
    Q_OBJECT
public:
    explicit ContextMenu(QWidget *parent = 0);

signals:
    void fileOrURLOpened(QString fileName);
    void stopClicked();

protected:

public slots:

private:
    URLDialog *urlDialog;
    void connectSignals();
    void setupUI();
    QMenu *openMenu;
    QAction *open;
    QAction *openURL;
    QAction *stop;
private slots:
    void openFile();
    void openURLClicked();
};

}

#endif // CONTEXTMENU_H
