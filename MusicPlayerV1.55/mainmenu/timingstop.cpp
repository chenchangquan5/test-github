#include "timingstop.h"
#include "ui_timingstop.h"

#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QStringList>

TimingStop::TimingStop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimingStop)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->rb_noSetTimingStop->setChecked(true);
    ui->cb_stopTimeHour->setEnabled(false);
    ui->cb_stopTimeMinute->setEnabled(false);
    ui->cb_totalTimeMinute->setEnabled(false);
    ui->cb_repetition->setEnabled(false);
    ui->pb_apply->setEnabled(false);

//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(timerDone()));
//    timer->start(2000);


}

TimingStop::~TimingStop()
{
    delete ui;
}

void TimingStop::on_rb_noSetTimingStop_clicked()
{
    ui->cb_stopTimeHour->setEnabled(false);
    ui->cb_stopTimeMinute->setEnabled(false);
    ui->cb_totalTimeMinute->setEnabled(false);
    ui->cb_repetition->setEnabled(false);
    ui->rb_noSetTimingStop->setChecked(true);
}

void TimingStop::on_rb_setTimingStop_clicked()
{
    ui->cb_stopTimeHour->setEnabled(true);
    ui->cb_stopTimeMinute->setEnabled(true);
    ui->cb_totalTimeMinute->setEnabled(true);
    ui->cb_repetition->setEnabled(true);
    ui->rb_setTimingStop->setChecked(true);
}

void TimingStop::on_pb_confirm_clicked()
{
    stopTotalTimeMinute();
    emit signalCloseTimingSettings();
}

void TimingStop::on_pb_apply_clicked()
{
    stopTotalTimeMinute();
    ui->pb_apply->setEnabled(false);
}

void TimingStop::on_pb_cancel_clicked()
{
    emit signalCloseTimingSettings();
}

void TimingStop::stopTotalTimeMinute(void)
{
    if(ui->rb_setTimingStop->isChecked() == true) //检测是否选中设置定时播放
    {
        int hour = ui->cb_stopTimeHour->currentIndex(); //读取ComBox中的小时值
        int minute = ui->cb_stopTimeMinute->currentIndex(); //读取ComBox中的分钟值
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

void TimingStop::updateCaption(void)
{
    qDebug() << "单触发";
    emit signalTimingStop();
}
