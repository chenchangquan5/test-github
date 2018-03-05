#include "timingsettings.h"
#include "ui_timingsettings.h"

#include <QWidget>
#include <QDebug>


TimingSettings::TimingSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimingSettings)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->wgt_timingPlay->close();
    ui->wgt_timingClose->close();

    connect(ui->wgt_timingStop,SIGNAL(signalCloseTimingSettings()),
            this,SLOT(slotCloseTimingSettings()));
    connect(ui->wgt_timingPlay,SIGNAL(signalCloseTimingSettings()),
            this,SLOT(slotCloseTimingSettings()));
    connect(ui->wgt_timingClose,SIGNAL(signalCloseTimingSettings()),
            this,SLOT(slotCloseTimingSettings()));
    connect(ui->wgt_timingStop,SIGNAL(signalTimingStop()),
            this,SLOT(slotTimingStop()));
    connect(ui->wgt_timingPlay,SIGNAL(signalTimingPlay()),
            this,SLOT(slotTimingPlay()));
    connect(ui->wgt_timingClose,SIGNAL(signalTimingClose()),
            this,SLOT(slotTimingClose()));
}

TimingSettings::~TimingSettings()
{
    delete ui;
}

void TimingSettings::on_pb_timingStop_clicked()
{
    ui->wgt_timingStop->show();
    ui->wgt_timingPlay->close();
    ui->wgt_timingClose->close();
}

void TimingSettings::on_pb_timingPlay_clicked()
{
    ui->wgt_timingPlay->show();
    ui->wgt_timingStop->close();
    ui->wgt_timingClose->close();
}

void TimingSettings::on_pb_timingClose_clicked()
{
    ui->wgt_timingClose->show();
    ui->wgt_timingPlay->close();
    ui->wgt_timingStop->close();
}

void TimingSettings::mousePressEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        m_dialogMove = ev->globalPos() - this->frameGeometry().topLeft();
        ev->accept();
    }
}

void TimingSettings::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        this->move(ev->globalPos() - m_dialogMove);
        ev->accept();
    }
}

void TimingSettings::on_pb_close_clicked()
{
    this->close();
}

void TimingSettings::slotCloseTimingSettings(void)
{
    this->close();
}

void TimingSettings::slotTimingStop(void)
{
    emit signalTimingSettingsToTimingStop();
}

void TimingSettings::slotTimingPlay(void)
{
    emit signalTimingSettingsToTimingPlay();
}

void TimingSettings::slotTimingClose(void)
{
    emit signalTimingSettingsToTimingClose();
}
