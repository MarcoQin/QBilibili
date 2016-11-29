#include "mainmenu.h"

using namespace UI;

namespace {
class ListProxyModel :public QSortFilterProxyModel
{
public:
    explicit ListProxyModel(QObject *parent = 0) :
        QSortFilterProxyModel(parent)
    {
//        setSourceModel(lApp->findObject<List>());
//        setSortRole(List::DateRole);
//        sort(0, Qt::DescendingOrder);
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        return role == Qt::DecorationRole ? QVariant() : QSortFilterProxyModel::data(index, role);
    }

//private:
//    bool filterAcceptsRow(int row, const QModelIndex &parent) const
//    {
//        QModelIndex i = sourceModel()->index(row, 0, parent);
//        if (!i.data(List::DateRole).toDateTime().isValid() || i.data(List::CodeRole).toInt() == List::Inherit){
//            return false;
//        }
//        QStandardItem *c = lApp->findObject<List>()->getCurrent();
//        return !c || c->index() != i;
//    }
};

class FileEdit :public QLineEdit
{
public:
    explicit FileEdit(QCompleter *completer, QWidget *parent = 0) :
        QLineEdit(parent), select(false), completer(completer)
    {
        connect(this, &QLineEdit::selectionChanged, [this](){
            select = 0;
        });
    }

private:
    bool select;
    QCompleter *completer;

    void mousePressEvent(QMouseEvent *e)
    {
        if (e->button() == Qt::LeftButton){
            select = 1;
        }
        QLineEdit::mousePressEvent(e);
    }

    void mouseReleaseEvent(QMouseEvent *e)
    {
        if (e->button() == Qt::LeftButton){
            if (select){
                completer->complete();
                completer->popup()->setCurrentIndex(completer->model()->index(0, 0));
            }
            select = 0;
        }
        QLineEdit::mouseReleaseEvent(e);
    }

    void focusInEvent(QFocusEvent *e)
    {
        //tab focus will cause whole selection
        if (e->reason() != Qt::TabFocusReason){
            QLineEdit::focusInEvent(e);
        }
    }
};

}


MainMenu::MainMenu(QWidget *parent) :
    QWidgetAction(parent)
{
}

Panel::Panel(QWidget *parent) :
    QWidget(parent)
{
    setupUI();
}

void Panel::setupUI(){
    mainLayout = new QGridLayout;
    ListProxyModel *fileModel = new ListProxyModel(this);
    fileCompleter = new QCompleter(fileModel, this);
    fileChooseLineEditor = new FileEdit(fileCompleter, this);
    fileChooseLineEditor->installEventFilter(this);
    fileChooseLineEditor->setReadOnly(true);
    fileChooseLineEditor->setPlaceholderText(tr("choose a local media"));
    mainLayout->addWidget(fileChooseLineEditor, 0, 0);
    fileCompleter->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    fileCompleter->setWidget(fileChooseLineEditor);
    fileChooseButton = new QPushButton(this);
    fileChooseButton->setText(tr("Open"));
    fileChooseButton->setStyleSheet("border-image:url(:/Picture/b_play.svg);");
    mainLayout->addWidget(fileChooseButton, 0, 1);
    alphaLabel = new QLabel(this);
    alphaLabel->setText(tr("Danmaku Alpha"));
    mainLayout->addWidget(alphaLabel, 1, 0);
    alphaSlider = new QSlider(this);
    alphaSlider->setOrientation(Qt::Horizontal);
    alphaSlider->setRange(0, 100);
    mainLayout->addWidget(alphaSlider, 1, 1);
    loopLabel = new QLabel(this);
    loopLabel->setText(tr("Loop Playback"));
    mainLayout->addWidget(loopLabel, 2, 0);
    loopCheckbox = new QCheckBox(this);
    mainLayout->addWidget(loopCheckbox, 2, 1);

    setLayout(mainLayout);
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
}

class Test : public QWidget
{
public:
    Test(QWidget *parent) :
        QWidget(parent)
    {
//        setAutoFillBackground(true);
//        QPalette palette = this->palette();
//        palette.setColor(QPalette::Window, Qt::white);
//        this->setPalette(palette);
//        219, 199, 188
        QHBoxLayout* pLayout = new QHBoxLayout();
        QLabel *pLabel = new QLabel ("title");
        pLayout->addWidget (pLabel);
        QSpinBox *pSpinBox = new QSpinBox(NULL);
        pLayout->addWidget (pSpinBox);
        setLayout (pLayout);
        QLabel *timeT = new QLabel(tr("Time"), this);
        QLabel *volmT = new QLabel(tr("Volume"), this);
        QSlider *timeS = new QSlider(this);
        QSlider *volmS = new QSlider(this);
        timeS->setOrientation(Qt::Horizontal);
        volmS->setOrientation(Qt::Horizontal);
        timeS->setRange(0, 0);
        volmS->setRange(0, 100);
        timeS->setValue(0);
        pLayout->addWidget(timeT);
        pLayout->addWidget(volmT);
        pLayout->addWidget(volmS);
        pLayout->addWidget(timeS);
        QPushButton *fileB = new QPushButton(this);
        fileB->setText(tr("Open"));
        pLayout->addWidget(fileB);
        QAction *fileA = new QAction(tr("Open File"), this);
        fileA->setObjectName("File");
        connect(fileA, &QAction::triggered, [this](){
            QString _file = QFileDialog::getOpenFileName();
            qDebug() << _file;
        });
        addAction(fileA);
        connect(fileB, &QPushButton::clicked, fileA, &QAction::trigger);
    }

};

QWidget* MainMenu::createWidget(QWidget *parent)
{
    return new Panel(parent);
}
