#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMouseEvent> //引用鼠标类头文件
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

signals:
    void signalControlPlay(void);
    void signalControlNext(void);
    void signalControlPrev(void);
    void signalControlPlayMode(int index);
    void signalControlSongNameListChangePlay(int index);
    void signalControlPosition(int position);
    void signalControlVolume(int volume);
    void signalNormalToMini(void);
    void signalCustomContexMenuRequested(int pos_x, int pos_y);
    void signalCloseSettingsDialog(void);
    void signalCloseTimingSettings(void);

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void setWidgetPlayButtonStyleSheet(QString style);
    void setWidgetPlayModeStyleSheet(QString mode);

    void setWidgetPlaylistSongs(QStringList list);
    void setWidgetCurrentSongNameList(int index, QString name);
    void setWidgetCurrentSongPositionTimeShow(QString &time);
    void setWidgetCurrentSongPosition(quint64 time);
    void setWidgetCurrentSongTotalTime(quint64 time);
    void setWidgetCurrentSongLyricList(QStringList list);
    void setWidgetCurrentLyricPlayRowShow(quint64 index);

protected:   
    void mousePressEvent(QMouseEvent *ev); //鼠标按下
    void mouseMoveEvent(QMouseEvent *ev); //鼠标移动
    void mouseDoubleClickEvent(QMouseEvent *ev);//鼠标双击

private slots:
    void on_pb_close_clicked();
    void on_pb_max_clicked();
    void on_pb_min_clicked();

    void on_pb_player_clicked();
    void on_pb_next_clicked();
    void on_pb_prev_clicked();
    void on_pb_playMode_clicked();
    void on_lw_songNameList_doubleClicked(const QModelIndex &index);

    void on_hs_position_sliderMoved(int position);
    void on_hs_volume_sliderMoved(int position);

    void on_pb_setting_clicked(); 
    void on_pb_mini_clicked();

private:
    Ui::MainWidget *ui;

    int num = 0;

    //QPoint last;

    //定义一个QPoint对象用于界面移动
    int m_playMode;
    QPoint m_wigetMove;

    QStringList m_currentLyricList;
    QMap<qint64, int> m_mapTimeToIndex;

    QMediaPlayer *m_player;
    QMediaPlaylist *m_mediaPlaylist;

    QStringList m_songNameList;

    qint64 m_totalPlayerTime;
    qint64 m_currentPlayTime;
    void initWidget(void);
};

#endif // MAINWIDGET_H
