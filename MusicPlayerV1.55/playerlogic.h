#ifndef PLAYERLOGIC_H
#define PLAYERLOGIC_H

#include <QObject>
#include <QMediaPlayer>
#include <QMenu>

#include "mainwidget.h"
#include "lyricfiles.h"
#include "settingsdialog.h"
#include "songfiles.h"
#include "miniwidget.h"
#include "timingsettings.h"


class PlayerLogic : public QObject
{
    Q_OBJECT

public slots:
    void slotChangePath(QString songPath, QString lyricPath);

    void slotControlPlay(void);
    void slotControlNext(void);
    void slotControlPrev(void);
    void slotControlPlayMode(int index);
    void slotControlSongNameListChangePlay(int index);
    void slotControlPosition(int position);
    void slotControlVolume(int volume);
    void slotControlSetting(void);
    void slotNormalToMini(void);
    void slotMiniToNormal(void);
    void slotCustomContexMenuRequested(int pos_x, int pos_y);
    void slotCloseWidget(void);
    void slotShowTimingSettings(void);
    void slotTimingSettingsToTimingStop(void);
    void slotTimingSettingsToTimingPlay(void);

public:
    explicit PlayerLogic(QObject *parent = 0);
    ~PlayerLogic();

    void showMainWidget(void);

signals:

private slots:
    void slotCurrentIndexChanged(int position);
    void slotDurationChanged(qint64 duration);
    void slotPositionChanged(qint64 position);

private:

    SettingsDialog *m_settingsDialog;
    void initSettingsDialog(void);

    int m_playIndex;
    int m_playMode;
    QMediaPlayer *m_player;
    void initPlayer(void);

    LyricFiles *m_lyricFiles;
    void getCurrentSongLyric(void);

    qint64 m_currentPlayerTime;
    qint64 m_totalPlayerTime;
    QString m_songName;
    QString m_playPosition;
    SongFiles *m_songFiles;
    QMediaPlaylist *m_playList;
    void initPlayList(void);

    MiniWidget *m_miniWidget;
    void initMiniWidget(void);

    //初始化主界面
    MainWidget *m_mainWidget;
    void initMainWidget(void);

    QMenu *m_menu;

    //初始化定时设置界面
    TimingSettings *m_timingSettings;
    void initTimingSettings(void);
};

#endif // PLAYERLOGIC_H
