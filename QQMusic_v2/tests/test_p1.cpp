#include <QtTest>
#include <QTemporaryDir>
#include <QTemporaryFile>
#include <QSignalSpy>
#include <QSettings>
#include <QElapsedTimer>
#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QDir>
#include <QLineEdit>

#include "../localsearchservice.h"
#include "../thememanager.h"
#include "../musicscanner.h"
#include "../musiclist.h"

class P1Test : public QObject
{
    Q_OBJECT
private slots:
    void searchHandlesTenThousandRecords()
    {
        QVector<Music> songs;
        songs.reserve(10000);
        for (int i = 0; i < 10000; ++i) {
            Music song;
            song.setMusicName(i == 9999 ? QStringLiteral("Target Song") : QStringLiteral("Song %1").arg(i));
            song.setMusicSinger(QStringLiteral("Singer %1").arg(i % 50));
            song.setMusicAlbumn(QStringLiteral("Album %1").arg(i % 100));
            songs.push_back(song);
        }
        QElapsedTimer timer;
        timer.start();
        const QVector<int> result = LocalSearchService::search(songs, QStringLiteral("target"));
        QVERIFY2(timer.elapsed() < 150, qPrintable(QStringLiteral("search took %1 ms").arg(timer.elapsed())));
        QCOMPARE(result.size(), 1);
        QCOMPARE(result.first(), 9999);
    }

    void themePersistsInIsolatedSettings()
    {
        QTemporaryDir settingsDir;
        QVERIFY(settingsDir.isValid());
        QSettings::setDefaultFormat(QSettings::IniFormat);
        QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, settingsDir.path());
        ThemeManager manager;
        QVERIFY(manager.themes().contains(QStringLiteral("dark")));
        QVERIFY(manager.apply(QStringLiteral("dark")));
        QCOMPARE(manager.currentTheme(), QStringLiteral("dark"));
        ThemeManager restored;
        restored.applySaved();
        QCOMPARE(restored.currentTheme(), QStringLiteral("dark"));
        QVERIFY(!manager.apply(QStringLiteral("missing")));
    }

    void themeOverridesWidgetLocalStyle()
    {
        QWidget sidePanel;
        sidePanel.setObjectName(QStringLiteral("bodyLeft"));
        sidePanel.setStyleSheet(QStringLiteral("#bodyLeft { background-color:#f0f0f0; }"));
        QLineEdit searchInput;
        searchInput.setObjectName(QStringLiteral("lineEdit"));
        searchInput.setStyleSheet(QStringLiteral("#lineEdit { background-color:#e3e3e3; }"));

        ThemeManager manager;
        QVERIFY(manager.apply(QStringLiteral("dark")));
        QVERIFY(sidePanel.styleSheet().contains(QStringLiteral("#242528")));
        QVERIFY(searchInput.styleSheet().contains(QStringLiteral("#3a3b3f")));
        QVERIFY(manager.apply(QStringLiteral("default")));
        QVERIFY(sidePanel.styleSheet().contains(QStringLiteral("#f0f0f0")));
    }

    void scannerFiltersUnsupportedFilesAndFinishesOffThread()
    {
        QTemporaryDir directory;
        QVERIFY(directory.isValid());
        QFile unsupported(directory.filePath(QStringLiteral("notes.txt")));
        QVERIFY(unsupported.open(QIODevice::WriteOnly));
        unsupported.write("not music");
        unsupported.close();
        QFile invalidAudio(directory.filePath(QStringLiteral("invalid.mp3")));
        QVERIFY(invalidAudio.open(QIODevice::WriteOnly));
        invalidAudio.write("not an MP3 file");
        invalidAudio.close();

        MusicScanner scanner;
        QSignalSpy finished(&scanner, &MusicScanner::finished);
        QSignalSpy cancelled(&scanner, &MusicScanner::cancelled);
        scanner.scan(QStringList() << directory.path());
        QTRY_VERIFY_WITH_TIMEOUT(finished.count() == 1, 5000);
        QCOMPARE(cancelled.count(), 0);
        const QList<QVariant> arguments = finished.takeFirst();
        QVERIFY(arguments.size() >= 3);
        QCOMPARE(qvariant_cast<QVector<ScannedMusic> >(arguments.at(0)).size(), 0);
        QCOMPARE(arguments.at(2).toStringList().size(), 1);
    }

    void scannerManualFixtureReportsExpectedSummary()
    {
        const QString invalidFixture = QFINDTESTDATA("../test-fixtures/p1-manual/invalid/not-audio.mp3");
        QVERIFY2(!invalidFixture.isEmpty(), "P1 manual fixture is missing");
        QDir fixtureRoot = QFileInfo(invalidFixture).dir();
        QVERIFY(fixtureRoot.cdUp());

        MusicScanner scanner;
        QSignalSpy finished(&scanner, &MusicScanner::finished);
        QSignalSpy cancelled(&scanner, &MusicScanner::cancelled);
        scanner.scan(QStringList() << fixtureRoot.absolutePath());
        QTRY_VERIFY_WITH_TIMEOUT(finished.count() == 1, 30000);
        QCOMPARE(cancelled.count(), 0);

        const QList<QVariant> arguments = finished.takeFirst();
        QCOMPARE(qvariant_cast<QVector<ScannedMusic> >(arguments.at(0)).size(), 4);
        QCOMPARE(arguments.at(1).toStringList().size(), 1);
        QCOMPARE(arguments.at(2).toStringList().size(), 1);
    }

    void scannedMusicMergesWithLegacyRecordByContent()
    {
        QTemporaryDir directory;
        QVERIFY(directory.isValid());
        const QString originalPath = directory.filePath(QStringLiteral("original.mp3"));
        const QString copiedPath = directory.filePath(QStringLiteral("copy.mp3"));
        QFile original(originalPath);
        QVERIFY(original.open(QIODevice::WriteOnly));
        original.write("same music content");
        original.close();
        QVERIFY(QFile::copy(originalPath, copiedPath));

        Music legacy;
        legacy.setMusicId(QStringLiteral("legacy"));
        legacy.setMusicUrl(QUrl::fromLocalFile(originalPath));
        legacy.setIsLike(true);

        QFile copied(copiedPath);
        QVERIFY(copied.open(QIODevice::ReadOnly));
        QCryptographicHash hash(QCryptographicHash::Sha1);
        hash.addData(QByteArray::number(copied.size()));
        hash.addData(copied.read(64 * 1024));
        const QString fingerprint = QString::fromLatin1(hash.result().toHex());

        Music scanned;
        scanned.setMusicId(QStringLiteral("scanned"));
        scanned.setMusicUrl(QUrl::fromLocalFile(copiedPath));
        scanned.setFingerprint(fingerprint);

        MusicList list;
        QCOMPARE(list.addScannedMusic(QVector<Music>() << legacy), 1);
        QCOMPARE(list.addScannedMusic(QVector<Music>() << scanned), 0);
        QCOMPARE(list.toVector().size(), 1);
        QVERIFY(list.toVector().first().getIsLike());
    }

    void scannerCanBeCancelled()
    {
        QTemporaryDir directory;
        QVERIFY(directory.isValid());
        for (int i = 0; i < 2000; ++i) {
            QDir dir(directory.path() + QStringLiteral("/d%1").arg(i % 20));
            QVERIFY(dir.mkpath(QStringLiteral(".")));
            QFile file(dir.filePath(QStringLiteral("%1.mp3").arg(i)));
            QVERIFY(file.open(QIODevice::WriteOnly));
            file.write("placeholder");
            file.close();
        }
        MusicScanner scanner;
        QSignalSpy cancelled(&scanner, &MusicScanner::cancelled);
        scanner.scan(QStringList() << directory.path());
        scanner.cancel();
        QTRY_VERIFY_WITH_TIMEOUT(cancelled.count() == 1, 5000);
        QVERIFY(!scanner.isRunning());
    }

    void deletedFileIsMarkedUnavailableWithoutRemovingRecord()
    {
        QTemporaryDir directory;
        QVERIFY(directory.isValid());
        const QString path = directory.filePath(QStringLiteral("song.mp3"));
        QFile file(path);
        QVERIFY(file.open(QIODevice::WriteOnly));
        file.write("placeholder");
        file.close();

        Music song;
        song.setMusicId(QStringLiteral("test-song"));
        song.setMusicUrl(QUrl::fromLocalFile(path));
        song.setMusicName(QStringLiteral("Test"));
        song.setFingerprint(QStringLiteral("fingerprint"));
        MusicList list;
        list.addScannedMusic(QVector<Music>() << song);
        QVERIFY(QFile::remove(path));
        QVERIFY(list.refreshAvailability());
        QCOMPARE(list.toVector().size(), 1);
        QVERIFY(!list.toVector().first().isAvailable());
    }
};

QTEST_MAIN(P1Test)
#include "test_p1.moc"
