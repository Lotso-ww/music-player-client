#include "music.h"
#include <QUuid>
#include <QMediaPlayer>
#include <QCoreApplication>
#include <QDebug>

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
    // 该函数需要在Music的构造函数中调⽤，当创建⾳乐对象时，顺便完成歌曲⽂件的加载
    parseMediaMetaData(); // 解析元数据
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

QString Music::getMusicLrcPath() const
{
    // 我们已经知道歌曲文件路径了
    // 歌词文件路径其实就是替换了一个后缀 .mp3->.lrc
    QString lrcPath = musicUrl.toString();
    lrcPath.replace(".mp3", ".lrc");
    lrcPath.replace(".flac", ".lrc");
    lrcPath.replace(".mpga", ".lrc");

    return lrcPath;
}

void Music::parseMediaMetaData()
{
    // 1. 创建媒体播放对象
    QMediaPlayer player;

    // 2. 设置媒体源,依靠setMedia方法解析元数据
    player.setMedia(musicUrl);

    // 3. 媒体元数据解析需要时间，只有等待解析完成之后，才能提取⾳乐信息，此处循环等待
    // 循环等待时：主界⾯消息循环就⽆法处理了，因此需要在等待解析期间，让消息循环继续处理
    while(!player.isMetaDataAvailable())
    {
        QCoreApplication::processEvents();
    }

    // 已经加载完成即可获取有效的元数据了
    if(player.isMetaDataAvailable())
    {
        musicName = player.metaData("Title").toString();
        musicSinger = player.metaData("Author").toString();
        musicAlbumn = player.metaData("AlbumTitle").toString();
        musicDuration = player.metaData("Duration").toLongLong();

        // 我们可以能在元数据里面有些歌曲基本信息获取不到，所以在文件中找一下
        QString fileName = musicUrl.fileName();
        // 找 - 的位置
        int index = fileName.indexOf('-');

        // musicName为 ""
        if(musicName.isEmpty())
        {
            // 能找到对应的 -
            // 2002年的第一场雪 - 刀郎.mp3
            if(index != - 1) // ! =
            {
                musicName = fileName.mid(0, index).trimmed();
            }
            // 2002年的第一场雪.mp3
            else
            {
                musicName = fileName.mid(0, fileName.indexOf('.')).trimmed();
            }
        }

        // musicSinger为 ""
        if(musicSinger.isEmpty())
        {
            if(index != -1)
            {
                musicSinger = fileName.mid(index + 2, fileName.indexOf('.') - index - 2).trimmed(); // +1, -1也可以,后续注意去掉空格
            }
            else
            {
                musicSinger = "未知歌手";
            }
        }

        // musicAlbumn
        if(musicAlbumn.isEmpty())
        {
            musicAlbumn = "未知专辑";
        }
        qDebug() << musicName << ":" << musicSinger << ":" << musicAlbumn << ":" << musicDuration;
    }
}
