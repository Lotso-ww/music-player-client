#include "musicscanner.h"
#include <QDirIterator>
#include <QFile>
#include <QCryptographicHash>
#include <QMetaObject>
#include <QMimeDatabase>
#include <QSet>

MusicScanner::MusicScanner(QObject *parent) : QObject(parent), m_running(0)
{
    qRegisterMetaType<QVector<ScannedMusic> >("QVector<ScannedMusic>");
    moveToThread(&m_thread);
    connect(&m_thread, &QThread::started, this, &MusicScanner::runScan);
}

MusicScanner::~MusicScanner()
{
    cancel();
    m_thread.quit();
    m_thread.wait();
}

void MusicScanner::scan(const QStringList &roots)
{
    if (m_running.loadAcquire() || roots.isEmpty()) return;
    m_roots = roots;
    m_cancelled.storeRelaxed(0);
    m_running.storeRelease(1);
    if (!m_thread.isRunning()) m_thread.start();
    else QMetaObject::invokeMethod(this, "runScan", Qt::QueuedConnection);
}

void MusicScanner::cancel() { m_cancelled.storeRelease(1); }

bool MusicScanner::isSupported(const QFileInfo &info)
{
    const QString suffix = info.suffix().toLower();
    return suffix == "mp3" || suffix == "flac" || suffix == "wav" || suffix == "aac" || suffix == "m4a";
}

bool MusicScanner::hasAudioHeader(const QFileInfo &info)
{
    QFile file(info.absoluteFilePath());
    if (!file.open(QIODevice::ReadOnly)) return false;
    const QByteArray header = file.read(16);
    const QString suffix = info.suffix().toLower();
    if (suffix == "flac") return header.startsWith("fLaC");
    if (suffix == "wav") return header.size() >= 12 && header.startsWith("RIFF") && header.mid(8, 4) == "WAVE";
    if (suffix == "m4a") return header.size() >= 8 && header.mid(4, 4) == "ftyp";
    if (suffix == "aac") return header.size() >= 2 &&
        static_cast<unsigned char>(header.at(0)) == 0xff &&
        (static_cast<unsigned char>(header.at(1)) & 0xf6) == 0xf0;
    // MP3 files commonly start with an ID3 tag or an MPEG frame sync.
    return header.startsWith("ID3") || (header.size() >= 2 &&
        static_cast<unsigned char>(header.at(0)) == 0xff &&
        (static_cast<unsigned char>(header.at(1)) & 0xe0) == 0xe0);
}

QString MusicScanner::fingerprint(const QFileInfo &info)
{
    QFile file(info.absoluteFilePath());
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

void MusicScanner::runScan()
{
    QStringList files;
    for (const QString &root : m_roots) {
        QFileInfo info(root);
        if (info.isFile() && isSupported(info)) files << info.absoluteFilePath();
        else if (info.isDir()) {
            QDirIterator it(root, QDir::Files, QDirIterator::Subdirectories);
            while (it.hasNext()) {
                if (m_cancelled.loadAcquire()) { m_running.storeRelease(0); emit cancelled(); return; }
                const QString path = it.next();
                if (isSupported(QFileInfo(path))) files << path;
            }
        }
    }
    const int total = files.size();
    QVector<ScannedMusic> items;
    QStringList duplicates;
    QStringList failures;
    QSet<QString> seenPaths;
    QSet<QString> seenFingerprints;
    for (int i = 0; i < total; ++i) {
        if (m_cancelled.loadAcquire()) { m_running.storeRelease(0); emit cancelled(); return; }
        const QFileInfo info(files.at(i));
        const QString path = info.absoluteFilePath();
        if (!hasAudioHeader(info)) {
            failures << path;
            emit progress(i + 1, total, path);
            continue;
        }
        const QString fp = fingerprint(info);
        if (seenPaths.contains(path) || (!fp.isEmpty() && seenFingerprints.contains(fp))) {
            duplicates << path;
        } else {
            seenPaths.insert(path);
            if (!fp.isEmpty()) seenFingerprints.insert(fp);
            ScannedMusic result;
            result.music = Music(QUrl::fromLocalFile(path));
            result.music.setFingerprint(fp);
            result.fingerprint = fp;
            if (result.music.getMusicUrl().isValid()) items.push_back(result);
            else failures << path;
        }
        emit progress(i + 1, total, path);
    }
    m_running.storeRelease(0);
    emit finished(items, duplicates, failures);
}
