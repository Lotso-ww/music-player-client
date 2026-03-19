#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QVector>
#include <QUrl>
#include "music.h"

// 管理所有歌曲对应的Music对象
class MusicList
{
public:
    MusicList();
    // 将QQMusic⻚⾯中读取到的⾳乐⽂件，检测是⾳乐⽂件后添加到musicList中
    void addMusicByUrl(const QList<QUrl>& musicUrls);
private:
    QVector<Music> musicList;
};

#endif // MUSICLIST_H
