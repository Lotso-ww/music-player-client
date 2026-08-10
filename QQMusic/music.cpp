#include "music.h"
#include <QUuid>
#include <QMediaPlayer>
#include <QCoreApplication>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QEventLoop>
#include <QTimer>
#include <QFileInfo>

Music::Music()
     : musicDuration(0)
     , isLike(false)
     , isHistory(false)
     , available(true)
{

}

Music::Music(const QUrl& url)
     : musicDuration(0)
     , isLike(false)
     , isHistory(false)
     , musicUrl(url)
     , available(true)
{
    // 读取url对应的歌曲文件信息，解析出元数据
    // 歌曲名称，歌曲作者，歌曲专辑，歌曲持续时长
    musicId = QUuid::createUuid().toString();
    // 该函数需要在Music的构造函数中调⽤，当创建⾳乐对象时，顺便完成歌曲⽂件的加载
    parseMediaMetaData(); // 解析元数据
}

// set系列
void Music::setMusicId(const QString &musicId)
{
    this->musicId = musicId;
}
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
void Music::setFingerprint(const QString &value) { fingerprint = value; }
void Music::setAvailable(bool value) { available = value; }

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
    QString lrcPath = musicUrl.toLocalFile();
    lrcPath.replace(".mp3", ".lrc");
    lrcPath.replace(".flac", ".lrc");
    lrcPath.replace(".mpga", ".lrc");

    return lrcPath;
}

bool Music::insertToDB()
{
    QSqlQuery query;
    // 1. 通过查询判断歌曲是否存在
    // query.prepare("SELECT * FROM MusicInfo WHERE musicId = ?"); // 查询所有列,效率低下,我们这里用不上
    // query.prepare("SELECT id FROM MusicInfo WHERE musicId = ?"); // 查询单列,但是还不够好
    // 在表中查询符合条件的歌曲,如果存在，返回记录中只有一个-1
    // 比如我们查出来符合条件的有三个,那么返回结果就是:
    // 1
    // 1
    // 1
    // query.prepare("SELECT 1 FROM MusicInfo WHERE musicId = ?");

    // 当SELECT 1...查询到结果后，我们需要知道是否存在
    // SELECT EXISTS(⼦查询) ： ⼦查询中如果有记录，SELECT EXISTS返回TRUE
    // 如果⼦查询中没有满⾜条件的记录， SELECT EXISTS返回FALSE
    query.prepare("SELECT EXISTS(SELECT 1 FROM MusicInfo WHERE musicId = ?)");
    query.addBindValue(musicId);
    if(!query.exec())
    {
        qDebug() << "查询失败" << query.lastError().text();
        return false;
    }

    if(query.next())
    {
        bool isExists = query.value(0).toBool();
        if(isExists)
        {
            // 2. 如果存在,那么我们就只需要更新数据库中对应的isLike和isHistory属性
            query.prepare("UPDATE MusicInfo SET isLike = ?, isHistory = ?, musicUrl = ?, available = ?, fingerprint = ? WHERE musicId = ?");
            query.addBindValue(isLike ? 1 : 0);
            query.addBindValue(isHistory ? 1 : 0);
            query.addBindValue(musicUrl.toLocalFile());
            query.addBindValue(available ? 1 : 0);
            query.addBindValue(fingerprint);
            query.addBindValue(musicId);
            if(!query.exec())
            {
                qDebug() << "更新失败" << query.lastError().text();
                return false;
            }
            qDebug() << "更新成功";
        }
        else
        {
            // 3. 如果不存在,我们就往数据库中插入对应的歌曲信息
            query.prepare("INSERT INTO MusicInfo(musicId, musicName, musicSinger, albumName,\
                                                 musicUrl, duration, isLike, isHistory, available, fingerprint)\
                           VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
            query.addBindValue(musicId);
            query.addBindValue(musicName);
            query.addBindValue(musicSinger);
            query.addBindValue(musicAlbumn);
            query.addBindValue(musicUrl.toLocalFile());
            query.addBindValue(musicDuration);
            query.addBindValue(isLike ? 1 : 0);
            query.addBindValue(isHistory ? 1 : 0);
            query.addBindValue(available ? 1 : 0);
            query.addBindValue(fingerprint);
            if(!query.exec())
            {
                qDebug() << "插入失败" << query.lastError().text();
                return false;
            }
            qDebug() << "插入成功";
        }
    }
    return true;
}
QString Music::getFingerprint() const { return fingerprint; }
bool Music::isAvailable() const { return available; }

void Music::parseMediaMetaData()
{
    // 1. 创建媒体播放对象
    QMediaPlayer player;

    // 2. 设置媒体源,依靠setMedia方法解析元数据
    player.setMedia(musicUrl);

    QEventLoop loop;
    QTimer timeout;
    timeout.setSingleShot(true);
    bool failed = false;
    QObject::connect(&player, &QMediaObject::metaDataAvailableChanged, &loop, [&](bool available) {
        if (available) loop.quit();
    });
    QObject::connect(&player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), &loop,
            [&](QMediaPlayer::Error) { failed = true; loop.quit(); });
    QObject::connect(&timeout, &QTimer::timeout, &loop, [&]() { failed = true; loop.quit(); });
    timeout.start(3000);
    if (!player.isMetaDataAvailable()) loop.exec();

    // 已经加载完成即可获取有效的元数据了
    if(player.isMetaDataAvailable() && !failed)
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
    }
    const QString fileName = QFileInfo(musicUrl.toLocalFile()).completeBaseName();
    if (musicName.isEmpty()) musicName = fileName.isEmpty() ? QStringLiteral("未知歌曲") : fileName;
    if (musicSinger.isEmpty()) musicSinger = QStringLiteral("未知歌手");
    if (musicAlbumn.isEmpty()) musicAlbumn = QStringLiteral("未知专辑");
    if (musicDuration < 0) musicDuration = 0;
}
