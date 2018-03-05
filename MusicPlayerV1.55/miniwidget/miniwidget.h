#ifndef MINIWIDGET_H
#define MINIWIDGET_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class MiniWidget;
}

class MiniWidget : public QWidget
{
    Q_OBJECT

signals:
    void signalControlPlay(void);
    void signalControlNext(void);
    void signalControlPrev(void);
    void signalControlPlayMode(int index);
    void signalControlPosition(int position);
    void signalControlVolume(int volume);
    void signalMiniToNormal(void);
    void signalCustomContexMenuRequested(int pos_x, int pos_y);
    void signalCloseSettingsDialog(void);
    void signalCloseTimingSettings(void);

public:
    explicit MiniWidget(QWidget *parent = 0);
    ~MiniWidget();

    void setMiniWidgetCurrentSongName(QString name);
    void setMiniWidgetPlayButtonStyleSheet(QString style);
    void setMiniWidgetPlayModeStyleSheet(QString mode);
    void setMiniWidgetCurrentSongPositionTimeShow(QString &time);
    void setMiniWidgetCurrentSongTotalTime(quint64 time);
    void setMiniWidgetCurrentSongPosition(quint64 time);

private slots:
    void on_pb_close_clicked();
    void on_pb_min_clicked();
    void on_pb_player_clicked();
    void on_pb_next_clicked();
    void on_pb_prev_clicked();
    void on_pb_playMode_clicked();
    void on_pb_normal_clicked();

    void on_hs_position_sliderMoved(int position);
    void on_hs_volumes_sliderMoved(int volume);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private:
    Ui::MiniWidget *ui;

    int m_playMode;

    QPoint m_widgetMove;
};

#endif // MINIWIDGET_H
