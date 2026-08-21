#include "musiclist.h"
#include "QMimeDatabase"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QCryptographicHash>
#include <QFile>
#include <QHash>
#include <QDir>

QString MusicList::normalizedPath(const QString &path)
{
    const QFileInfo info(path);
    const QString canonical = info.canonicalFilePath();
    return QDir::cleanPath(canonical.isEmpty() ? info.absoluteFilePath() : canonical);
}

QString MusicList::fingerprintForPath(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return QString();
    QCryptographicHash hash(QCryptographicHash::Sha1);
    const qint64 size = file.size();
    hash.addData(QByteArray::number(size));
    hash.addData(file.read(64 * 1024));
    if (size > 64 * 1024) {
        file.seek(qMax<qint64>(0, size - 64 * 1024));
        hash.addData(file.read(64 * 1024));
    }
    return QString::fromLatin1(hash.result().toHex());
}

void MusicList::mergeMusic(Music &target, const Music &duplicate)
{
    target.setIsLike(target.getIsLike() || duplicate.getIsLike());
    target.setIsHistory(target.getIsHistory() || duplicate.getIsHistory());
    if (target.getFingerprint().isEmpty()) target.setFingerprint(duplicate.getFingerprint());
    if (!target.isAvailable() && duplicate.isAvailable()) {
        target.setMusicUrl(duplicate.getMusicUrl());
        target.setAvailable(true);
    }
}

void MusicList::rebuildIndexes()
{
    musicPaths.clear();
    musicFingerprints.clear();
    for (const Music &music : musicList) {
        const QString path = normalizedPath(music.getMusicUrl().toLocalFile());
        if (!path.isEmpty()) musicPaths.insert(path);
        if (!music.getFingerprint().isEmpty()) musicFingerprints.insert(music.getFingerprint());
    }
}
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
        QString musicPath = normalizedPath(musicurl.toLocalFile());
        if(musicPaths.contains(musicPath)) continue;

        // 歌曲还没有加载过，将其解析并添加到歌曲列表

        // 由于添加进来的⽂件不⼀定是歌曲文件，因此需要再次筛选出音乐文件
        QMimeDatabase mimeDB;
        QMimeType mimeType = mimeDB.mimeTypeForFile(musicurl.toLocalFile());
        QString mime = mimeType.name();

        // audio/mpeg ： 适⽤于mp3格式的⾳频文件  audio/flac : 表⽰⽆损⾳频压缩格式  audio/wav : 表⽰wav格式的歌曲⽂件
        // 如果是音乐文件, 加⼊歌曲列表
        if(mime == "audio/mpeg" || mime == "audio/flac" || mime == "audio/wav")
        {
            musicPaths.insert(musicPath);
            // 需要将url创建一个Music对象添加至musicList中
            Music music(musicurl);
            musicList.push_back(music);
        }
    }
    rebuildIndexes();
}

void MusicList::readFromDB()
{
    QSqlQuery query;
    query.prepare("SELECT musicId, musicName, musicSinger, albumName,\
                   musicUrl, duration, isLike, isHistory, available, fingerprint FROM MusicInfo");
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
        if (query.record().count() > 8) music.setAvailable(query.value(8).toBool());
        if (query.record().count() > 9) music.setFingerprint(query.value(9).toString());
        musicList.push_back(music);

        // 防止歌曲恢复导致歌曲添加重复问题复现
        musicPaths.insert(music.getMusicUrl().toLocalFile()); // 我们上面setMusicUrl如果不是这样的形式的话不仅对我的歌区封面歌词等有影响, 对这个也有
        if (!music.getFingerprint().isEmpty()) musicFingerprints.insert(music.getFingerprint());
    }
    removeDuplicates();
    rebuildIndexes();
}

bool MusicList::writeToDB()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen() || !db.transaction()) return false;
    for(auto& music : musicList) {
        if(!music.insertToDB()) { db.rollback(); return false; }
    }
    for (const QString &musicId : deletedMusicIds) {
        QSqlQuery deleteQuery;
        deleteQuery.prepare("DELETE FROM MusicInfo WHERE musicId = ?");
        deleteQuery.addBindValue(musicId);
        if (!deleteQuery.exec()) { db.rollback(); return false; }
    }
    if (!db.commit()) { db.rollback(); return false; }
    deletedMusicIds.clear();
    return true;
}

int MusicList::addScannedMusic(const QVector<Music> &items)
{
    const int previousCount = musicList.size();
    for (const Music &music : items) {
        const QString path = normalizedPath(music.getMusicUrl().toLocalFile());
        if (path.isEmpty()) continue;
        if (!music.getFingerprint().isEmpty() && musicFingerprints.contains(music.getFingerprint())) {
            for (iterator it = begin(); it != end(); ++it) {
                if (it->getFingerprint() == music.getFingerprint() && !QFileInfo::exists(it->getMusicUrl().toLocalFile())) {
                    it->setMusicUrl(music.getMusicUrl());
                    it->setAvailable(true);
                }
            }
            continue;
        }
        if (musicPaths.contains(path)) continue;
        musicPaths.insert(path);
        if (!music.getFingerprint().isEmpty()) musicFingerprints.insert(music.getFingerprint());
        musicList.push_back(music);
    }
    removeDuplicates();
    rebuildIndexes();
    return qMax(0, musicList.size() - previousCount);
}

bool MusicList::removeDuplicates()
{
    bool changed = false;
    QHash<QString, int> pathIndex;
    QHash<QString, int> fingerprintIndex;
    QMultiHash<qint64, int> fingerprintSizeIndex;
    QVector<Music> unique;
    unique.reserve(musicList.size());

    for (const Music &music : musicList) {
        const QString path = normalizedPath(music.getMusicUrl().toLocalFile());
        if (!path.isEmpty() && pathIndex.contains(path)) {
            mergeMusic(unique[pathIndex.value(path)], music);
            deletedMusicIds.insert(music.getMusicId());
            changed = true;
            continue;
        }
        if (music.getFingerprint().isEmpty()) continue;
        if (fingerprintIndex.contains(music.getFingerprint())) {
            mergeMusic(unique[fingerprintIndex.value(music.getFingerprint())], music);
            deletedMusicIds.insert(music.getMusicId());
            changed = true;
            continue;
        }
        const int index = unique.size();
        unique.push_back(music);
        fingerprintIndex.insert(music.getFingerprint(), index);
        fingerprintSizeIndex.insert(QFileInfo(path).size(), index);
        if (!path.isEmpty()) pathIndex.insert(path, index);
    }

    for (const Music &music : musicList) {
        if (!music.getFingerprint().isEmpty()) continue;
        const QString path = normalizedPath(music.getMusicUrl().toLocalFile());
        if (!path.isEmpty() && pathIndex.contains(path)) {
            mergeMusic(unique[pathIndex.value(path)], music);
            deletedMusicIds.insert(music.getMusicId());
            changed = true;
            continue;
        }
        const QString fingerprint = fingerprintSizeIndex.contains(QFileInfo(path).size()) ? fingerprintForPath(path) : QString();
        if (!fingerprint.isEmpty() && fingerprintIndex.contains(fingerprint)) {
            mergeMusic(unique[fingerprintIndex.value(fingerprint)], music);
            deletedMusicIds.insert(music.getMusicId());
            changed = true;
            continue;
        }
        const int index = unique.size();
        unique.push_back(music);
        if (!path.isEmpty()) pathIndex.insert(path, index);
    }

    if (changed) musicList = unique;
    return changed;
}

bool MusicList::refreshAvailability()
{
    bool changed = false;
    for (iterator it = begin(); it != end(); ++it) {
        const bool available = QFileInfo::exists(it->getMusicUrl().toLocalFile());
        if (it->isAvailable() != available) {
            it->setAvailable(available);
            changed = true;
        }
    }
    return changed;
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
