#include "musiclist.h"
#include "QMimeDatabase"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
MusicList::MusicList()
{

}

void MusicList::addMusicByUrl(const QList<QUrl> &musicUrls)
{
    // 将所有的音乐放置到musicList中
    for(auto& musicurl : musicUrls)
    {
//        // 这个算法的时间复杂度是O(n)
//        auto it = begin();
//        for(; it!=end(); ++it)
//        {
//            if(it->getMusicUrl() == musicurl)
//                break;
//        }
//        if(it != end()) continue;

        // 查找: 最快的就是哈希 Qset O(1)
        // 检测歌曲是否存在，如果不在才能添加
        QString musicPath = musicurl.toLocalFile();
        if(musicPaths.contains(musicPath)) continue;

        // 歌曲还没有加载过，将其解析并添加到歌曲列表
         musicPaths.insert(musicPath);


        // 由于添加进来的⽂件不⼀定是歌曲文件，因此需要再次筛选出音乐文件
        QMimeDatabase mimeDB;
        QMimeType mimeType = mimeDB.mimeTypeForFile(musicurl.toLocalFile());
        QString mime = mimeType.name();

        // audio/mpeg ： 适⽤于mp3格式的⾳频文件  audio/flac : 表⽰⽆损⾳频压缩格式  audio/wav : 表⽰wav格式的歌曲⽂件
        // 如果是音乐文件, 加⼊歌曲列表
        if(mime == "audio/mpeg" || mime == "audio/flac" || mime == "audio/wav")
        {
            // 需要将url创建一个Music对象添加至musicList中
            Music music(musicurl);
            musicList.push_back(music);
        }
    }
}

void MusicList::readFromDB()
{
    QSqlQuery query;
    query.prepare("SELECT musicId, musicName, musicSinger, albumName,\
                   musicUrl, duration, isLike, isHistory FROM MusicInfo");
    if(!query.exec())
    {
        qDebug() << "数据库查询失败!!! " << query.lastError().text();
        return;
    }

    while(query.next())
    {
        Music music;
        music.setMusicId(query.value(0).toString());
        music.setMusicName(query.value(1).toString());
        music.setMusicSinger(query.value(2).toString());
        music.setMusicAlbumn(query.value(3).toString());
        music.setMusicUrl(QUrl::fromLocalFile(query.value(4).toString()));
        music.setMusicDuration(query.value(5).toLongLong());
        music.setIsLike(query.value(6).toBool());
        music.setIsHistory(query.value(7).toBool());
        musicList.push_back(music);

        // 防止歌曲恢复导致歌曲添加重复问题复现
        musicPaths.insert(music.getMusicUrl().toLocalFile()); // 我们上面setMusicUrl如果不是这样的形式的话不仅对我的歌区封面歌词等有影响, 对这个也有
    }
}

void MusicList::writeToDB()
{
    for(auto& music : musicList)
    {
        // 循环遍历这个歌曲列表
        // 将每个music的信息写入进数据库里
        music.insertToDB();
    }
}

iterator MusicList::findMusicById(const QString &musicId)
{
    for(iterator it = begin(); it != end(); ++it)
    {
        if(it->getMusicId() == musicId)
            return it;
    }

    return end(); // 代表没找到
}

iterator MusicList::begin()
{
    return musicList.begin();
}

iterator MusicList::end()
{
    return musicList.end();
}
