#include "playerlogic.h"

#include <QDebug>
#include <QTime>
#include <QFont>

PlayerLogic::PlayerLogic(QObject *parent) : QObject(parent)
{
    initMainWidget();
    initMiniWidget();
    initSettingsDialog();
    initTimingSettings();
    initPlayList();
    initPlayer();
}

PlayerLogic::~PlayerLogic()
{

}

void PlayerLogic::initMainWidget(void)
{
    m_mainWidget = new MainWidget;

    connect(m_mainWidget,SIGNAL(signalControlPlay()),
            this,SLOT(slotControlPlay()));
    connect(m_mainWidget,SIGNAL(signalControlNext()),
            this,SLOT(slotControlNext()));
    connect(m_mainWidget,SIGNAL(signalControlPrev()),
            this,SLOT(slotControlPrev()));
    connect(m_mainWidget,SIGNAL(signalControlPlayMode(int)),
            this,SLOT(slotControlPlayMode(int)));
    connect(m_mainWidget,SIGNAL(signalControlSongNameListChangePlay(int)),
            this,SLOT(slotControlSongNameListChangePlay(int)));
    connect(m_mainWidget,SIGNAL(signalControlPosition(int)),
            this,SLOT(slotControlPosition(int)));
    connect(m_mainWidget,SIGNAL(signalControlVolume(int)),
            this,SLOT(slotControlVolume(int)));
    connect(m_mainWidget,SIGNAL(signalNormalToMini()),
            this,SLOT(slotNormalToMini()));
    connect(m_mainWidget,SIGNAL(signalCustomContexMenuRequested(int,int)),
            this,SLOT(slotCustomContexMenuRequested(int,int)));
}

void PlayerLogic::showMainWidget(void)
{
    m_mainWidget->show();
}

void PlayerLogic::initPlayList(void)
{
    m_lyricFiles = new LyricFiles;
    m_lyricFiles->setLyricPath(m_settingsDialog->getLyricPath());

    m_songFiles = new SongFiles;
    m_songFiles->currentSongNamePath(m_settingsDialog->getSongPath());

    m_playList = new QMediaPlaylist;
    foreach (QString songSource, m_songFiles->getSongSourceList())
    {
        m_playList->addMedia(QUrl(songSource));
    }
    m_mainWidget->setWidgetPlaylistSongs(m_songFiles->getSongNameList());

    m_playMode = 3;
    m_playList->setPlaybackMode(QMediaPlaylist::Loop);

    connect(m_playList,SIGNAL(currentIndexChanged(int)),
            this,SLOT(slotCurrentIndexChanged(int)));
}

void PlayerLogic::initPlayer(void)
{
    m_player = new QMediaPlayer;
    m_player->setPlaylist(m_playList);
    m_player->setVolume(50);

    m_playIndex = 0;
    m_playList->setCurrentIndex(m_playIndex);

    connect(m_player,SIGNAL(durationChanged(qint64)),
            this,SLOT(slotDurationChanged(qint64)));
    connect(m_player,SIGNAL(positionChanged(qint64)),
            this,SLOT(slotPositionChanged(qint64)));
}

void PlayerLogic::slotChangePath(QString songPath, QString lyricPath)
{
    m_lyricFiles->setLyricPath(lyricPath);
    m_songFiles->currentSongNamePath(songPath);

    m_playList->clear();

    foreach (QString songSourse, m_songFiles->getSongSourceList())
    {
        m_playList->addMedia(QUrl(songSourse));
    }

    m_mainWidget->setWidgetPlaylistSongs(m_songFiles->getSongNameList());
    //如果getSongNameList()换成了getSongSourceList(),则在播放列表中显示路径
}

void PlayerLogic::initSettingsDialog(void)
{
    m_settingsDialog = new SettingsDialog;
    connect(m_settingsDialog,SIGNAL(signalChangePath(QString,QString)),
            this,SLOT(slotChangePath(QString,QString)));
    connect(m_mainWidget,SIGNAL(signalCloseSettingsDialog()),
            m_settingsDialog,SLOT(slotCloseSettingsDialog()));
    connect(m_miniWidget,SIGNAL(signalCloseSettingsDialog()),
            m_settingsDialog,SLOT(slotCloseSettingsDialog()));
}

void PlayerLogic::initTimingSettings(void)
{
    m_timingSettings = new TimingSettings;
    connect(m_mainWidget,SIGNAL(signalCloseTimingSettings()),
            m_timingSettings,SLOT(slotCloseTimingSettings()));
    connect(m_miniWidget,SIGNAL(signalCloseTimingSettings()),
            m_timingSettings,SLOT(slotCloseTimingSettings()));
    connect(m_timingSettings,SIGNAL(signalTimingSettingsToTimingStop()),
            this,SLOT(slotTimingSettingsToTimingStop()));
    connect(m_timingSettings,SIGNAL(signalTimingSettingsToTimingPlay()),
            this,SLOT(slotTimingSettingsToTimingPlay()));
    connect(m_timingSettings,SIGNAL(signalTimingSettingsToTimingClose()),
            this,SLOT(slotCloseWidget()));
}

void PlayerLogic::initMiniWidget(void)
{
    m_miniWidget = new MiniWidget;

    connect(m_miniWidget,SIGNAL(signalControlPlay()),
            this,SLOT(slotControlPlay()));
    connect(m_miniWidget,SIGNAL(signalControlNext()),
            this,SLOT(slotControlNext()));
    connect(m_miniWidget,SIGNAL(signalControlPrev()),
            this,SLOT(slotControlPrev()));
    connect(m_miniWidget,SIGNAL(signalControlPosition(int)),
            this,SLOT(slotControlPosition(int)));
    connect(m_miniWidget,SIGNAL(signalControlVolume(int)),
            this,SLOT(slotControlVolume(int)));
    connect(m_miniWidget,SIGNAL(signalControlPlayMode(int)),
            this,SLOT(slotControlPlayMode(int)));
    connect(m_miniWidget,SIGNAL(signalMiniToNormal()),
            this,SLOT(slotMiniToNormal()));
    connect(m_miniWidget,SIGNAL(signalCustomContexMenuRequested(int,int)),
            this,SLOT(slotCustomContexMenuRequested(int,int)));
}

void PlayerLogic::slotDurationChanged(qint64 duration)
{
    m_currentPlayerTime = 0;
    m_totalPlayerTime = duration / 1000;  //获取到的duration总时间以毫秒为单位，
                                          //故除以1000，

    QTime currentTime((m_currentPlayerTime/3600)%60,(m_currentPlayerTime/60)%60,
                     m_currentPlayerTime%60,(m_currentPlayerTime*1000)/1000);
    QTime totalTime((m_totalPlayerTime/3600)%60,(m_totalPlayerTime/60)%60,
                    m_totalPlayerTime%60,(m_totalPlayerTime*1000)/1000);

    m_playPosition = currentTime.toString("mm:ss") + "/"
                     + totalTime.toString("mm:ss");

    m_mainWidget->setWidgetCurrentSongPositionTimeShow(m_playPosition);
    m_mainWidget->setWidgetCurrentSongTotalTime(m_totalPlayerTime);

    m_miniWidget->setMiniWidgetCurrentSongPositionTimeShow(m_playPosition);
    m_miniWidget->setMiniWidgetCurrentSongTotalTime(m_totalPlayerTime);
}

void PlayerLogic::slotPositionChanged(qint64 position)
{
    m_currentPlayerTime = position / 1000; //获取到的position实时时间以毫秒为单位

    QTime currentTime((m_currentPlayerTime/3600)%60,(m_currentPlayerTime/60)%60,
                     m_currentPlayerTime%60,(m_currentPlayerTime*1000)/1000);
    QTime totalTime((m_totalPlayerTime/3600)%60,(m_totalPlayerTime/60)%60,
                    m_totalPlayerTime%60,(m_totalPlayerTime*1000)/1000);

    m_playPosition = currentTime.toString("mm:ss") + "/"
                     + totalTime.toString("mm:ss");

    if(m_lyricFiles->getMapLyricIndex().contains(m_currentPlayerTime))
    {
        m_mainWidget->setWidgetCurrentLyricPlayRowShow(m_lyricFiles->getMapLyricIndex().value(m_currentPlayerTime));
    }

    m_mainWidget->setWidgetCurrentSongPositionTimeShow(m_playPosition);
    m_mainWidget->setWidgetCurrentSongPosition(m_currentPlayerTime);

    m_miniWidget->setMiniWidgetCurrentSongPositionTimeShow(m_playPosition);
    m_miniWidget->setMiniWidgetCurrentSongPosition(m_currentPlayerTime);
}

void PlayerLogic::slotCurrentIndexChanged(int position)
{
    m_songName = m_songFiles->getSongNameList().at(position);
    m_mainWidget->setWidgetCurrentSongNameList(position,m_songName);
    m_miniWidget->setMiniWidgetCurrentSongName(m_songName);

    getCurrentSongLyric();
}

void PlayerLogic::getCurrentSongLyric(void)
{
    m_lyricFiles->getCurrentLyric(m_songName);
    m_mainWidget->setWidgetCurrentSongLyricList(m_lyricFiles->getLyricList());
}

void PlayerLogic::slotControlPlay(void)
{
    if(m_player->state() == QMediaPlayer::PlayingState)
    {
        m_player->pause();
        m_mainWidget->setWidgetPlayButtonStyleSheet("border-image:"
                        "url(:/skins/images/playStartNormal.png)");
        m_miniWidget->setMiniWidgetPlayButtonStyleSheet("border-image:"
                        "url(:/skins/images/playStartNormal.png)");
    }else
    {
        m_player->play();
        m_mainWidget->setWidgetPlayButtonStyleSheet("border-image:"
                           "url(:/skins/images/pauseNormal.png);");
        m_miniWidget->setMiniWidgetPlayButtonStyleSheet("border-image:"
                           "url(:/skins/images/pauseNormal.png);");
    }
}

void PlayerLogic::slotControlNext(void)
{
    m_playIndex = m_playList->nextIndex();
    if(m_playIndex == -1)
    {
        m_player->stop();
        m_mainWidget->setWidgetPlayButtonStyleSheet("border-image: url(:/skins/images/pauseNormal.png);");
    }else
    {
        m_playList->setCurrentIndex(m_playIndex);
    }
}

void PlayerLogic::slotControlPrev(void)
{
    m_playIndex = m_playList->previousIndex();
    if(m_playIndex == -1)
    {
        m_player->stop();
        m_mainWidget->setWidgetPlayButtonStyleSheet("border-image:"
                            "url(:/skins/images/pauseNormal.png);");
    }else
    {
        m_playList->setCurrentIndex(m_playIndex);
    }
}

void PlayerLogic::slotControlPlayMode(int index)
{
    m_playMode = index;
    switch(m_playMode)
    {
    case QMediaPlaylist::CurrentItemOnce:
        m_playList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        m_mainWidget->setWidgetPlayModeStyleSheet("border-image:"
               "url(:/skins/images/currentItemOnceNormal.png);");
        m_miniWidget->setMiniWidgetPlayModeStyleSheet("border-image:"
               "url(:/skins/images/currentItemOnceNormal.png);");
        break;
    case QMediaPlaylist::CurrentItemInLoop:
        m_playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        m_mainWidget->setWidgetPlayModeStyleSheet("border-image:"
               "url(:/skins/images/currentItemInLoopNormal.png);");
        m_miniWidget->setMiniWidgetPlayModeStyleSheet("border-image:"
               "url(:/skins/images/currentItemInLoopNormal.png);");
        break;
    case QMediaPlaylist::Sequential:
        m_playList->setPlaybackMode(QMediaPlaylist::Sequential);
        m_mainWidget->setWidgetPlayModeStyleSheet("border-image:"
               "url(:/skins/images/sequentialNormal.png);");
        m_miniWidget->setMiniWidgetPlayModeStyleSheet("border-image:"
               "url(:/skins/images/sequentialNormal.png);");
        break;
    case QMediaPlaylist::Loop:
        m_playList->setPlaybackMode(QMediaPlaylist::Loop);
        m_mainWidget->setWidgetPlayModeStyleSheet("border-image:"
               "url(:/skins/images/loopNormal.png);");
        m_miniWidget->setMiniWidgetPlayModeStyleSheet("border-image:"
               "url(:/skins/images/loopNormal.png);");
        break;
    case QMediaPlaylist::Random:
        m_playList->setPlaybackMode(QMediaPlaylist::Random);
        m_mainWidget->setWidgetPlayModeStyleSheet("border-image:"
               "url(:/skins/images/randomNormal.png);");
        m_miniWidget->setMiniWidgetPlayModeStyleSheet("border-image:"
               "url(:/skins/images/randomNormal.png);");
        break;
    default:break;
    }
}

void PlayerLogic::slotControlSongNameListChangePlay(int index)
{
    m_playList->setCurrentIndex(index);
    m_player->play();
}

void PlayerLogic::slotControlPosition(int position)
{
    m_player->setPosition(position*1000);
}

void PlayerLogic::slotControlVolume(int volume)
{
    m_player->setVolume(volume);
}

void PlayerLogic::slotControlSetting()
{
    m_settingsDialog->show();
}

void PlayerLogic::slotNormalToMini()
{
    m_mainWidget->hide();
    m_miniWidget->show();
}

void PlayerLogic::slotMiniToNormal()
{
    m_miniWidget->hide();
    m_mainWidget->show();
}

void PlayerLogic::slotCustomContexMenuRequested(int pos_x, int pos_y)
{
    m_menu = new QMenu;

    QMenu addSong("添加歌曲");
    addSong.addAction("添加本地歌曲...");
    addSong.addAction("添加本地歌曲文件夹...");
    addSong.setFont(QFont("Arial",13));

    QMenu addMenuMode("播放模式");
    addMenuMode.addAction("单曲播放");
    addMenuMode.addAction("单曲循环");
    addMenuMode.addAction("顺序播放");
    addMenuMode.addAction("列表播放");
    addMenuMode.addAction("随机播放");
    addMenuMode.setFont(QFont("Arial",13));

    m_menu->addAction("注销");
    m_menu->addSeparator();
    m_menu->addMenu(&addSong);
    m_menu->addMenu(&addMenuMode);
    m_menu->addAction("定时设置",this,SLOT(slotShowTimingSettings()));
    m_menu->addSeparator();
    m_menu->addAction("界面总在最前");
    m_menu->addAction("帮助");
    m_menu->addAction("设置",this,SLOT(slotControlSetting()));
    m_menu->addSeparator();
    m_menu->addAction("退出",this,SLOT(slotCloseWidget()));
    m_menu->setFont(QFont("Arial",15));
    m_menu->setGeometry(pos_x,pos_y,0,0);
    m_menu->exec();
}

void PlayerLogic::slotCloseWidget(void)
{
    m_mainWidget->close();
    m_timingSettings->close();
}

void PlayerLogic::slotShowTimingSettings(void)
{
    m_timingSettings->show();
}

void PlayerLogic::slotTimingSettingsToTimingStop(void)
{
    m_player->stop();
}

void PlayerLogic::slotTimingSettingsToTimingPlay(void)
{
    m_player->play();
}
