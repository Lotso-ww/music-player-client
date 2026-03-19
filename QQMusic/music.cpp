#include "music.h"
#include <QUuid>

Music::Music()
     : isLike(false)
     , isHistory(false)
{

}

Music::Music(const QUrl& url)
     : isLike(false)
     , isHistory(false)
     , musicUrl(url)
{
    // 读取url对应的歌曲文件信息，解析出元数据
    // 歌曲名称，歌曲作者，歌曲专辑，歌曲持续时长
    musicId = QUuid::createUuid().toString();
}

// set系列
void Music::setMusicName(const QString& musicName)
{
    this->musicName = musicName;
}
void Music::setMusicSinger(const QString& musicSinger)
{
    this->musicSinger = musicSinger;
}
void Music::setMusicAlbumn(const QString& musicAlbumn)
{
    this->musicAlbumn = musicAlbumn;
}
void Music::setMusicDuration(const qint64 musicDuration)
{
    this->musicDuration = musicDuration;
}
void Music::setIsLike(bool isLike)
{
    this->isLike = isLike;
}
void Music::setIsHistory(bool isHistory)
{
    this->isHistory = isHistory;
}
void Music::setMusicUrl(const QUrl& musicUrl)
{
    this->musicUrl = musicUrl;
}

// get系列
QString Music::getMusicId()const
{
    return musicId;
}
QString Music::getMusicName()const
{
    return musicName;
}
QString Music::getMusicSinger()const
{
    return musicSinger;
}
QString Music::getMusicAlbumn()const
{
    return musicAlbumn;
}
qint64 Music::getMusicDuration()const
{
    return musicDuration;
}
bool Music::getIsLike()const
{
    return isLike;
}
bool Music::getIsHistory()const
{
    return isHistory;
}
QUrl Music::getMusicUrl()const
{
    return musicUrl;
}
