#include "timingplay.h"
#include "ui_timingplay.h"

#include <QDebug>
#include <QTime>
#include <QTimer>

TimingPlay::TimingPlay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimingPlay)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->rb_noSetTimingPlay->setChecked(true);
    ui->cb_playTimeHour->setEnabled(false);
    ui->cb_playTimeMinute->setEnabled(false);
    ui->cb_repetition->setEnabled(false);
    ui->cb_list->setEnabled(false);
    ui->cb_chapter->setEnabled(false);
}

TimingPlay::~TimingPlay()
{
    delete ui;
}

void TimingPlay::on_rb_noSetTimingPlay_clicked()
{
    ui->cb_playTimeHour->setEnabled(false);
    ui->cb_playTimeMinute->setEnabled(false);
    ui->cb_repetition->setEnabled(false);
    ui->cb_list->setEnabled(false);
    ui->cb_chapter->setEnabled(false);
}

void TimingPlay::on_rb_setTimingPlay_clicked()
{
    ui->cb_playTimeHour->setEnabled(true);
    ui->cb_playTimeMinute->setEnabled(true);
    ui->cb_repetition->setEnabled(true);
    ui->cb_list->setEnabled(true);
    ui->cb_chapter->setEnabled(true);
}

void TimingPlay::on_pb_confirm_clicked()
{
    playTotalTimeMinute();
}

void TimingPlay::on_pb_apply_clicked()
{
    playTotalTimeMinute();
}

void TimingPlay::on_pb_cancel_clicked()
{
    signalCloseTimingSettings();
}

void TimingPlay::playTotalTimeMinute(void)
{
    if(ui->rb_setTimingPlay->isChecked() == true) //检测是否选中设置定时播放
    {
        int hour = ui->cb_playTimeHour->currentIndex(); //读取ComBox中的小时值
        int minute = ui->cb_playTimeMinute->currentIndex(); //读取ComBox中的分钟值
        int totalTimeMinute;

        QTime time;
        QString currentTime = time.currentTime().toString("hh:mm:ss"); //获取系统实时时间
        QStringList hourAndMinute = currentTime.split(":");
        QString currentHour = hourAndMinute.at(0); //系统时间中的小时
        QString currentMinute = hourAndMinute.at(1);  //系统时间中的分钟
        int totalHour,totalMinute;

        if(currentHour.toInt() >= hour)  //当系统的小时大于等于输入的小时，两者相差的时间
        {
            totalHour = 23 - currentHour.toInt() + hour;
            totalHour %= 24;

            if(((60 - currentMinute.toInt()) + minute) >= 60)
            {
                totalHour += 1;
                totalMinute = (60 - currentMinute.toInt()) + minute - 60;
            }else
            {
                totalMinute = (60 - currentMinute.toInt()) + minute;
            }

            if(minute == 0)
            {
                totalMinute -= 1;
            }

            if((currentHour.toInt() == hour) && (currentMinute.toInt() <= minute))
            {
                totalHour = 0;
            }
        }else //当系统的小时小于输入的小时，两者相差的时间
        {
            totalHour = hour - currentHour.toInt() - 1;
            if(((60 - currentMinute.toInt()) + minute) >= 60)
            {
                totalHour += 1;
                totalMinute = (60 - currentMinute.toInt()) + minute - 60;
            }else
            {
                totalMinute = (60 - currentMinute.toInt()) + minute;
            }
        }

        qDebug() << totalHour << " " << totalMinute;

        totalTimeMinute = totalHour*60 + totalMinute; //以分钟为单位，相差的时间
        qDebug() << totalTimeMinute;

        //单触发定时器
        QTimer::singleShot(totalTimeMinute*60*1000, this, SLOT(updateCaption()));
    }
}

void TimingPlay::updateCaption(void)
{
    qDebug() << "单触发";
    emit signalTimingPlay();
}


