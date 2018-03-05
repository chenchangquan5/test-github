#include "miniwidget.h"
#include "ui_miniwidget.h"

#include <QDebug>

MiniWidget::MiniWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiniWidget)
{
    ui->setupUi(this);

    //当光标移动到以下部件时，变为手型
    ui->pb_close->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_min->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_next->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_player->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_playMode->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_prev->setCursor(QCursor(Qt::PointingHandCursor));
    ui->hs_position->setCursor(QCursor(Qt::PointingHandCursor));
    ui->hs_volumes->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pb_normal->setCursor(QCursor(Qt::PointingHandCursor));

    this->setWindowFlags(Qt::FramelessWindowHint);
}

MiniWidget::~MiniWidget()
{
    delete ui;
}

void MiniWidget::setMiniWidgetCurrentSongName(QString name)
{
    ui->lb_songName->setText(name);
}

void MiniWidget::setMiniWidgetPlayButtonStyleSheet(QString style)
{
    ui->pb_player->setStyleSheet(style);
}

void MiniWidget::setMiniWidgetPlayModeStyleSheet(QString mode)
{
    ui->pb_playMode->setStyleSheet(mode);
}

void MiniWidget::setMiniWidgetCurrentSongPositionTimeShow(QString &time)
{
    ui->lb_position->setText(time);
}

void MiniWidget::setMiniWidgetCurrentSongTotalTime(quint64 time)
{
    ui->hs_position->setMaximum(time);
}

void MiniWidget::setMiniWidgetCurrentSongPosition(quint64 time)
{
    if(!ui->hs_position->isSliderDown())//不被按下时
    {
        ui->hs_position->setValue(time);
    }
}

void MiniWidget::on_pb_close_clicked()
{
    emit signalCloseSettingsDialog();
    emit signalCloseTimingSettings();
    this->close();
}

void MiniWidget::on_pb_min_clicked()
{
    this->showMinimized();
}

void MiniWidget::on_pb_player_clicked()
{
    emit signalControlPlay();
}

void MiniWidget::on_pb_next_clicked()
{
    emit signalControlNext();
}

void MiniWidget::on_pb_prev_clicked()
{
    emit signalControlPrev();
}

void MiniWidget::on_hs_position_sliderMoved(int position)
{
    emit signalControlPosition(position);
}

void MiniWidget::on_hs_volumes_sliderMoved(int volume)
{
    emit signalControlVolume(volume);
}

void MiniWidget::on_pb_normal_clicked()
{
    emit signalMiniToNormal();
}

//当鼠标左键按下时，获取主窗体左顶角的位置
void MiniWidget::mousePressEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        m_widgetMove = ev->globalPos() - this->frameGeometry().topLeft();
        ev->accept(); //鼠标事件被接收
    }

    if(ev->buttons() == Qt::RightButton)
    {
        emit signalCustomContexMenuRequested(ev->globalX(),ev->globalY());
    }
}
//当鼠标左键按下时，即可移动主窗体
void MiniWidget::mouseMoveEvent(QMouseEvent *ev)
{
    this->move(ev->globalPos() - m_widgetMove);
    ev->accept();
}

void MiniWidget::on_pb_playMode_clicked()
{
    m_playMode++;
    m_playMode %= 5;
    emit signalControlPlayMode(m_playMode);
}
