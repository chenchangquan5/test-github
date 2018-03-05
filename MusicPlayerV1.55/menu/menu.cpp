#include "menu.h"
#include "ui_menu.h"

#include <QDebug>
#include <QHBoxLayout>


Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    m_addAction = new QAction(tr("tianjia"),this);
//    QAction *m_deletAction = new QAction(tr("shanchu"),this);
//    QAction *m_quitAction = new QAction(tr("tuichu"),this);

    m_label = new QLabel;

//    QHBoxLayout *boxLayout = new QHBoxLayout(this);
//    boxLayout->addWidget(m_label);

//    QMenuBar *BoxLayout = new QMenuBar;
//    BoxLayout->addAction(addAction);
//    BoxLayout->addAction(deletAction);
//    BoxLayout->addAction(quitAction);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::slotShowMenu(int globalX, int globalY)
{
    this->setGeometry(globalX,globalY,151,392);
    this->show();
}

void Menu::slotCloseMenu(void)
{
    this->close();
}

