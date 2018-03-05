#include "songfiles.h"

#include <QDir>
#include <QFileInfoList>
#include <QUrl>
#include <QStringList>
#include <QDebug>

SongFiles::SongFiles(QObject *parent) : QObject(parent)
{
    m_songPath.clear();
    m_songNameList.clear();
    m_songSourceList.clear();
}

SongFiles::~SongFiles()
{

}

void SongFiles::currentSongNamePath(const QString songPath)
{
    m_songPath = songPath;
    QDir d(m_songPath);
    QFileInfoList list = d.entryInfoList(QStringList() << "*.mp3",
                                         QDir::Files, QDir::Time);
    m_songNameList.clear();

//    for(int i = 0; i < list.length(); i++)
//    {
//        m_songNameList.append(list.at(i).baseName());
//        m_songSourceList.append(list.at(i).absoluteFilePath());
//    }

    foreach(const QFileInfo &info, list)
    {
        m_songNameList.append(info.baseName());
        m_songSourceList.append(info.absoluteFilePath());
    }
}

const QStringList &SongFiles::getSongNameList(void)
{
    return m_songNameList;
}

const QStringList &SongFiles::getSongSourceList(void)
{
    return m_songSourceList;
}
