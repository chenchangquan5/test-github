#ifndef SONGFILES_H
#define SONGFILES_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "mainwidget.h"

class SongFiles : public QObject
{
    Q_OBJECT
public:
    explicit SongFiles(QObject *parent = 0);
    ~SongFiles();

    void currentSongNamePath(const QString songPath);
    const QStringList &getSongNameList(void);
    const QStringList &getSongSourceList(void);

private:
    QString m_songPath;
    QStringList m_songNameList;
    QStringList m_songSourceList;
};

#endif // SONGFILES_H
