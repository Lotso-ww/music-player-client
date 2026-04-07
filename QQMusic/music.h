#ifndef MUSIC_H
#define MUSIC_H

#include <QUrl>

class Music
{
public:
    Music();
    Music(const QUrl& url);

public:
    // set系列
    void setMusicName(const QString& musicName);
    void setMusicSinger(const QString& musicSinger);
    void setMusicAlbumn(const QString& musicAlbumn);
    void setMusicDuration(const qint64 musicDuration);
    void setIsLike(bool isLike);
    void setIsHistory(bool isHistory);
    void setMusicUrl(const QUrl& musicUrl);

    // get系列
    QString getMusicId()const;
    QString getMusicName()const;
    QString getMusicSinger()const;
    QString getMusicAlbumn()const;
    qint64 getMusicDuration()const;
    bool getIsLike()const;
    bool getIsHistory()const;
    QUrl getMusicUrl()const;
    QString getMusicLrcPath()const;

    void insertToDB();

private:
    void parseMediaMetaData(); // 解析元数据
private:
    // 为了保证歌曲的唯一性，需要给音乐添加id
    // 磁盘上的歌曲⽂件经常删除或者修改位置，导致播放时找不到⽂件，或者重复添加
    // 此处⽤musicId来维护播放列表中⾳乐的唯⼀性
    QString musicId;

    // 基本信息: 歌曲名称 歌曲作者 歌曲专辑 歌曲持续时长
    QString musicName;
    QString musicSinger;
    QString musicAlbumn;
    qint64 musicDuration; // qint64 -- long long

    // 其它: 歌曲是否喜欢 歌曲是否为历史播放 歌曲Url
    bool isLike;
    bool isHistory;
    QUrl musicUrl;
};

#endif // MUSIC_H
