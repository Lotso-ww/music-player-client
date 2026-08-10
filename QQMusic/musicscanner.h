#ifndef MUSICSCANNER_H
#define MUSICSCANNER_H

#include <QObject>
#include <QThread>
#include <QAtomicInt>
#include <QVector>
#include <QStringList>
#include <QFileInfo>
#include "music.h"

struct ScannedMusic
{
    Music music;
    QString fingerprint;
};
Q_DECLARE_METATYPE(ScannedMusic)
Q_DECLARE_METATYPE(QVector<ScannedMusic>)

class MusicScanner : public QObject
{
    Q_OBJECT
public:
    explicit MusicScanner(QObject *parent = nullptr);
    ~MusicScanner();
    void scan(const QStringList &roots);
    void cancel();
    bool isRunning() const { return m_running.loadAcquire() != 0; }

signals:
    void progress(int scanned, int total, const QString &path);
    void finished(const QVector<ScannedMusic> &items, const QStringList &duplicates, const QStringList &failures);
    void cancelled();

private slots:
    void runScan();

private:
    static bool isSupported(const QFileInfo &info);
    static bool hasAudioHeader(const QFileInfo &info);
    static QString fingerprint(const QFileInfo &info);
    QAtomicInt m_cancelled;
    QAtomicInt m_running;
    QStringList m_roots;
    QThread m_thread;
};

#endif
