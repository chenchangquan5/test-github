#include "lyricfiles.h"

#include <QFile>
#include <QTextStream>

LyricFiles::LyricFiles(QObject *parent) : QObject(parent)
{

}

LyricFiles::~LyricFiles()
{

}

void LyricFiles::getCurrentLyric(QString songName)
{
    QString fileName = m_lyricPath + "/" + songName + ".lrc";
    QFile lyricFile(fileName);

    if(lyricFile.open(QIODevice::ReadOnly))
    {
        QTextStream ts(&lyricFile);
        quint64 index = 0;
        m_mapLyicIndex.clear();
        m_lyricList.clear();
        while(!ts.atEnd())
        {
            QString line = ts.readLine();
            QStringList posAndLyric = line.split("]");
            QString pos = posAndLyric.at(0).mid(0,6);
            QString lyric = posAndLyric.at(1);
            QStringList minuteAndSecond = pos.remove("[").split(":");
            quint64 time = minuteAndSecond.at(0).toInt()*60 + minuteAndSecond.at(1).toInt();
            m_mapLyicIndex.insert(time,index);
            m_lyricList.append(lyric);
            index++;
            posAndLyric.clear();
        }
    }
    lyricFile.close();
}

void LyricFiles::setLyricPath(QString lyricPath)
{
    m_lyricPath = lyricPath;
}

QStringList LyricFiles::getLyricList(void)
{
    return m_lyricList;
}

QMap<quint64, quint64> LyricFiles::getMapLyricIndex(void)
{
    return m_mapLyicIndex;
}
