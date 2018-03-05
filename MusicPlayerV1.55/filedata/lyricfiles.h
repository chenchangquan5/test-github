#ifndef LYRICFILES_H
#define LYRICFILES_H

#include <QObject>
#include <QMap>

class LyricFiles : public QObject
{
    Q_OBJECT
public:
    explicit LyricFiles(QObject *parent = 0);
    ~LyricFiles();

    void getCurrentLyric(QString songName);
    void setLyricPath(QString lyricPath);
    QStringList getLyricList(void);
    QMap<quint64, quint64> getMapLyricIndex(void);

private:
    QString m_lyricPath;
    QStringList m_lyricList;
    QMap<quint64, quint64> m_mapLyicIndex;
};

#endif // LYRICFILES_H
