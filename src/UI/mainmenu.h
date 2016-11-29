#ifndef MAINMENU_H
#define MAINMENU_H
#include <Qt>
#include <QtWidgets>
#include <QWidgetAction>

namespace UI {

class MainMenu : public QWidgetAction
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget * parent);
protected:
    QWidget * createWidget(QWidget *parent);
};

class Panel : public QWidget{
    Q_OBJECT
public:
    Panel(QWidget *parent);
private:
    QLineEdit *fileChooseLineEditor;
    QLineEdit *danmChooseLineEditor;
    QCompleter *fileCompleter;
    QCompleter *danmCompleter;
    QPushButton *fileChooseButton;
    QPushButton *danmChooseButton;
    QAction *openFileAction;
    QAction *loadDanmAction;
    QLabel *alphaLabel;
    QSlider *alphaSlider;
    QLabel *loopLabel;
    QCheckBox *loopCheckbox;

    QGridLayout *mainLayout;
    void setupUI();
};


}
#endif // MAINMENU_H
