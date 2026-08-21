#include "localsearchservice.h"
#include "music.h"

bool LocalSearchService::matches(const Music &music, const QString &query)
{
    const QString normalized = query.trimmed();
    if (normalized.isEmpty()) return true;
    const Qt::CaseSensitivity cs = Qt::CaseInsensitive;
    return music.getMusicName().contains(normalized, cs)
        || music.getMusicSinger().contains(normalized, cs)
        || music.getMusicAlbumn().contains(normalized, cs);
}

QVector<int> LocalSearchService::search(const QVector<Music> &musicList, const QString &query)
{
    QVector<int> result;
    result.reserve(musicList.size());
    for (int i = 0; i < musicList.size(); ++i) {
        if (matches(musicList.at(i), query)) result.push_back(i);
    }
    return result;
}
