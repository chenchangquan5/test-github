#ifndef TIMINGSETTINGS_H
#define TIMINGSETTINGS_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class TimingSettings;
}

class TimingSettings : public QDialog
{
    Q_OBJECT

signals:
    void signalTimingSettingsToTimingStop(void);
    void signalTimingSettingsToTimingPlay(void);
    void signalTimingSettingsToTimingClose(void);

public slots:
    void slotCloseTimingSettings(void);
    void slotTimingStop(void);
    void slotTimingPlay(void);
    void slotTimingClose(void);

public:
    explicit TimingSettings(QWidget *parent = 0);
    ~TimingSettings();

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private slots:
    void on_pb_timingStop_clicked();
    void on_pb_timingPlay_clicked();
    void on_pb_timingClose_clicked();
    void on_pb_close_clicked();

private:
    Ui::TimingSettings *ui;

    QPoint m_dialogMove;
};

#endif // TIMINGSETTINGS_H
