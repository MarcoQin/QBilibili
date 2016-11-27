#include "popmenu.h"

#include <Qt>
#include <QtWidgets>

PopMenu::PopMenu(QWidget * parent) :
    QWidgetAction(parent)
{

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
    }

};


QWidget* PopMenu::createWidget(QWidget *parent)
{
    return new Test(parent);
}
