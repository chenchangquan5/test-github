#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "songfiles.h"

#include <QWidget>
#include <QDir>
#include <QFileInfoList>
#include <QStringList>
#include <QUrl>
#include <QDebug>
#include <QMenu>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    //当光标移动到以下部件时，变为手型
    ui->pb_close->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_login->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_max->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_min->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_mini->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_next->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_player->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_playMode->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_prev->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_setting->setCursor(QCursor(Qt::PointingHandCursor));
    ui->hs_position->setCursor(QCursor(Qt::PointingHandCursor));
    ui->hs_volume->setCursor(QCursor(Qt::PointingHandCursor));
    ui->lw_lyricShow->setCursor(QCursor(Qt::OpenHandCursor));

    initWidget();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::initWidget(void)
{
    this->setWindowFlags(Qt::FramelessWindowHint);

    //隐藏水平方向和垂直方向的滚动条
    ui->lw_songNameList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->lw_songNameList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->lw_lyricShow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->lw_lyricShow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWidget::setWidgetPlaylistSongs(QStringList list)
{
    ui->lw_songNameList->clear();
    ui->lw_songNameList->addItems(list);
}

void MainWidget::setWidgetCurrentSongNameList(int index, QString name)
{
    ui->lw_songNameList->setCurrentRow(index);
    ui->lb_songName->setText(name);
}

void MainWidget::setWidgetCurrentSongLyricList(QStringList list)
{
    ui->lw_lyricShow->clear();
    ui->lw_lyricShow->addItems(list);
}

void MainWidget::setWidgetCurrentLyricPlayRowShow(quint64 index)
{
    ui->lw_lyricShow->setCurrentRow(index);
}

void MainWidget::setWidgetPlayButtonStyleSheet(QString style)
{
    ui->pb_player->setStyleSheet(style);
}

void MainWidget::setWidgetPlayModeStyleSheet(QString mode)
{
    ui->pb_playMode->setStyleSheet(mode);
}

void MainWidget::setWidgetCurrentSongPositionTimeShow(QString &time)
{
    ui->lb_position->setText(time);
}

void MainWidget::setWidgetCurrentSongTotalTime(quint64 time)
{
    ui->hs_position->setMaximum(time);
}

void MainWidget::setWidgetCurrentSongPosition(quint64 time)
{
    if(!ui->hs_position->isSliderDown())//不被按下时
    {
        ui->hs_position->setValue(time);
    }
}

void MainWidget::on_pb_close_clicked()
{
    emit signalCloseSettingsDialog();
    emit signalCloseTimingSettings();
    this->close();
}

void MainWidget::on_pb_max_clicked()
{
    if(this->isMaximized())
    {
        this->showNormal();
    }else
    {
        this->showMaximized();
    }
}

void MainWidget::on_pb_min_clicked()
{
    this->showMinimized();
}

//获取鼠标点定位窗体位置
//void MainWidget::mousePressEvent(QMouseEvent *ev)
//{
//    last = ev->globalPos();
//}
//void MainWidget::mouseMoveEvent(QMouseEvent *ev)
//{
//    int dx = ev->globalX() - last.x();
//    int dy = ev->globalY() - last.y();
//    last = ev->globalPos();
//    move(x()+dx,y()+dy);
//}
//void MainWidget::mouseReleaseEvent(QMouseEvent *ev)
//{
//    int dx = ev->globalX() - last.x();
//    int dy = ev->globalY() - last.y();
//    move(x()+dx,y()+dy);
//}


//当按下鼠标左键时，获取主窗体左上角的位置
void MainWidget::mousePressEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        m_wigetMove = ev->globalPos() - this->frameGeometry().topLeft();
        ev->accept();  //鼠标事件被系统接收
    }

    if(ev->buttons() == Qt::RightButton)
    {
        emit signalCustomContexMenuRequested(ev->globalX(), ev->globalY());
    }
}
//当按下鼠标左键时，移动左窗体
void MainWidget::mouseMoveEvent(QMouseEvent *ev)
{
    if(isMaximized())
    {
        this->showNormal();
    }else
    {
        if(ev->buttons() == Qt::LeftButton)
        {
            this->move(ev->globalPos() - m_wigetMove);
            ev->accept();
        }
    }
}
//当双击鼠标左键时，执行事件
void MainWidget::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        if(this->isMaximized())
        {
            this->showNormal();
        }else
        {
            this->showMaximized();
        }
    }
}

void MainWidget::on_pb_player_clicked()
{
    emit signalControlPlay();
}

void MainWidget::on_pb_next_clicked()
{
    emit signalControlNext();
}

void MainWidget::on_pb_prev_clicked()
{
    emit signalControlPrev();
}


void MainWidget::on_pb_playMode_clicked()
{
    m_playMode++;
    m_playMode %= 5;
    emit signalControlPlayMode(m_playMode);
}

void MainWidget::on_lw_songNameList_doubleClicked(const QModelIndex &index)
{
    emit signalControlSongNameListChangePlay(index.row());
    ui->pb_player->setStyleSheet("border-image:"
                                 "url(:/skins/images/pauseNormal.png);");
}

void MainWidget::on_hs_position_sliderMoved(int position)
{
    emit signalControlPosition(position);
}

void MainWidget::on_hs_volume_sliderMoved(int position)
{
    emit signalControlVolume(position);
}

void MainWidget::on_pb_setting_clicked()
{
    ++num;
    num %= 2;
    switch(num)
    {
    case 0: break;
    case 1: emit signalCustomContexMenuRequested(frameGeometry().x() + 815,
                                                 frameGeometry().y() + 66);
        break;
    default: break;
    }
}

void MainWidget::on_pb_mini_clicked()
{
    emit  signalNormalToMini();
}


