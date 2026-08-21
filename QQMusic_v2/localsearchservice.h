#ifndef LOCALSEARCHSERVICE_H
#define LOCALSEARCHSERVICE_H

#include <QVector>
#include <QString>

class Music;

class LocalSearchService
{
public:
    static bool matches(const Music &music, const QString &query);
    static QVector<int> search(const QVector<Music> &musicList, const QString &query);
};

#endif
