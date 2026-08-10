#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QVector>
#include <QUrl>
#include <QSet>
#include "music.h"

// 管理所有歌曲对应的Music对象
typedef QVector<Music>::iterator iterator;
class MusicList
{
public:
    MusicList();
    // 将QQMusic⻚⾯中读取到的⾳乐⽂件，检测是⾳乐⽂件后添加到musicList中
    void addMusicByUrl(const QList<QUrl>& musicUrls);
    int addScannedMusic(const QVector<Music> &items);
    bool removeDuplicates();
    bool refreshAvailability();
    void readFromDB(); // 从数据库中读取
    bool writeToDB(); // 歌曲信息写入数据库
    iterator findMusicById(const QString& musicId);
    iterator begin();
    iterator end();
    QVector<Music> toVector() const { return musicList; }

private:
    static QString normalizedPath(const QString &path);
    static QString fingerprintForPath(const QString &path);
    static void mergeMusic(Music &target, const Music &duplicate);
    void rebuildIndexes();
    QVector<Music> musicList;
    QSet<QString> musicPaths; // 防止添加歌曲文件时重复加载
    QSet<QString> musicFingerprints;
    QSet<QString> deletedMusicIds;
};

#endif // MUSICLIST_H
