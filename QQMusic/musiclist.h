#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QVector>
#include <QUrl>
#include "music.h"

// 管理所有歌曲对应的Music对象
typedef QVector<Music>::iterator iterator;
class MusicList
{
public:
    MusicList();
    // 将QQMusic⻚⾯中读取到的⾳乐⽂件，检测是⾳乐⽂件后添加到musicList中
    void addMusicByUrl(const QList<QUrl>& musicUrls);
    void readFromDB(); // 从数据库中读取
    void writeToDB(); // 歌曲信息写入数据库
    iterator findMusicById(const QString& musicId);
    iterator begin();
    iterator end();

private:
    QVector<Music> musicList;
};

#endif // MUSICLIST_H
