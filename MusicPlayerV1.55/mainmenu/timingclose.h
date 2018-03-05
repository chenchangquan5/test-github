#ifndef TIMINGCLOSE_H
#define TIMINGCLOSE_H

#include <QWidget>

namespace Ui {
class TimingClose;
}

class TimingClose : public QWidget
{
    Q_OBJECT

signals:
    void signalTimingClose(void);
    void signalCloseTimingSettings(void);

public slots:
    void updateCaption(void);

public:
    explicit TimingClose(QWidget *parent = 0);
    ~TimingClose();

    void closeTotalTimeMinute(void);

private slots:
    void on_rb_noSetTimingClose_clicked();
    void on_rb_setTimingClose_clicked();

    void on_pb_confirm_clicked();
    void on_pb_apply_clicked();
    void on_pb_cancel_clicked();

private:
    Ui::TimingClose *ui;
};

#endif // TIMINGCLOSE_H
