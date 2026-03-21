#include "musiclist.h"
#include "QMimeDatabase"
#include <QDebug>
MusicList::MusicList()
{

}

void MusicList::addMusicByUrl(const QList<QUrl> &musicUrls)
{
    // 将所有的音乐放置到musicList中
    for(auto& musicurl : musicUrls)
    {
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
