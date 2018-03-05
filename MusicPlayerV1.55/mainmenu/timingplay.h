#ifndef TIMINGPLAY_H
#define TIMINGPLAY_H

#include <QWidget>

namespace Ui {
class TimingPlay;
}

class TimingPlay : public QWidget
{
    Q_OBJECT

signals:
    void signalTimingPlay(void);
    void signalCloseTimingSettings(void);

public slots:
    void updateCaption(void);

public:
    explicit TimingPlay(QWidget *parent = 0);
    ~TimingPlay();

    void playTotalTimeMinute(void);

private slots:
    void on_rb_noSetTimingPlay_clicked();
    void on_rb_setTimingPlay_clicked();

    void on_pb_confirm_clicked();
    void on_pb_apply_clicked();
    void on_pb_cancel_clicked();

private:
    Ui::TimingPlay *ui;
};

#endif // TIMINGPLAY_H
