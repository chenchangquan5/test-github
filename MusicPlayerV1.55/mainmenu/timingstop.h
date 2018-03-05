#ifndef TIMINGSTOP_H
#define TIMINGSTOP_H

#include <QWidget>

namespace Ui {
class TimingStop;
}

class TimingStop : public QWidget
{
    Q_OBJECT

signals:
    void signalTimingStop(void);
    void signalCloseTimingSettings(void);

public slots:
    void updateCaption(void);

public:
    explicit TimingStop(QWidget *parent = 0);
    ~TimingStop();

    void stopTotalTimeMinute(void);

private slots:
    void on_rb_noSetTimingStop_clicked();
    void on_rb_setTimingStop_clicked();

    void on_pb_confirm_clicked();
    void on_pb_apply_clicked();
    void on_pb_cancel_clicked();

private:
    Ui::TimingStop *ui;
};

#endif // TIMINGSTOP_H
