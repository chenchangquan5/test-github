#include "timingclose.h"
#include "ui_timingclose.h"

#include <QDebug>
#include <QTime>
#include <QTimer>

TimingClose::TimingClose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimingClose)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->rb_noSetTimingClose->setChecked(true);
    ui->cb_closeTimeHour->setEnabled(false);
    ui->cb_closeTimeMinute->setEnabled(false);
    ui->cb_repetition->setEnabled(false);
    ui->cb_totalTimeMinute->setEnabled(false);
}

TimingClose::~TimingClose()
{
    delete ui;
}

void TimingClose::on_rb_noSetTimingClose_clicked()
{
    ui->cb_closeTimeHour->setEnabled(false);
    ui->cb_closeTimeMinute->setEnabled(false);
    ui->cb_repetition->setEnabled(false);
    ui->cb_totalTimeMinute->setEnabled(false);
}

void TimingClose::on_rb_setTimingClose_clicked()
{
    ui->cb_closeTimeHour->setEnabled(true);
    ui->cb_closeTimeMinute->setEnabled(true);
    ui->cb_repetition->setEnabled(true);
    ui->cb_totalTimeMinute->setEnabled(true);
}

void TimingClose::on_pb_confirm_clicked()
{
    closeTotalTimeMinute();
}

void TimingClose::on_pb_apply_clicked()
{
    closeTotalTimeMinute();
}

void TimingClose::on_pb_cancel_clicked()
{
    signalCloseTimingSettings();
}

void TimingClose::closeTotalTimeMinute(void)
{
    if(ui->rb_setTimingClose->isChecked() == true) //检测是否选中设置定时播放
    {
        int hour = ui->cb_closeTimeHour->currentIndex(); //读取ComBox中的小时值
        int minute = ui->cb_closeTimeMinute->currentIndex(); //读取ComBox中的分钟值
        int totalTimeMinute = ui->cb_totalTimeMinute->currentIndex();

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

void TimingClose::updateCaption(void)
{
    qDebug() << "单触发";
    emit signalTimingClose();
}
