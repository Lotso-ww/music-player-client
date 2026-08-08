#include <QtTest>
#include <QTemporaryFile>
#include <QTextStream>
#include "../lrcpage.h"
#include "../recbox.h"

class P0Test : public QObject
{
    Q_OBJECT
private slots:
    void lrcFractionsAndMultipleTags()
    {
        QTemporaryFile file;
        QVERIFY(file.open());
        QTextStream stream(&file);
        stream << "[00:01.2][00:02.34]first\n[00:03.456]second\n";
        stream.flush();
        LrcPage page;
        QVERIFY(page.parseLrc(file.fileName()));
        QCOMPARE(page.getWordIndex(1200), 0);
        QCOMPARE(page.getWordIndex(2340), 1);
        QCOMPARE(page.getWordIndex(3456), 2);
    }

    void lrcLegacyDoubleFractionFormat()
    {
        QTemporaryFile file;
        QVERIFY(file.open());
        file.write("[0:9.970.00]legacy line\n[0:19.940.00]next line\n");
        file.flush();
        LrcPage page;
        QVERIFY(page.parseLrc(file.fileName()));
        QCOMPARE(page.getWordIndex(9970), 0);
        QCOMPARE(page.getWordIndex(19940), 1);
    }

    void lrcRejectsInvalidAndClearsOldData()
    {
        QTemporaryFile valid;
        QVERIFY(valid.open());
        valid.write("[00:01.000]old\n");
        valid.flush();
        QTemporaryFile invalid;
        QVERIFY(invalid.open());
        invalid.write("[00:99.000]bad\nnot a tag\n");
        invalid.flush();
        LrcPage page;
        QVERIFY(page.parseLrc(valid.fileName()));
        QVERIFY(!page.parseLrc(invalid.fileName()));
        QCOMPARE(page.getWordIndex(1000), -1);
    }

    void recommendationKeepsTail()
    {
        QCOMPARE(RecBox::pageCount(0, 4), 0);
        QCOMPARE(RecBox::pageCount(1, 4), 1);
        QCOMPARE(RecBox::pageCount(9, 4), 3);
        QCOMPARE(RecBox::pageCount(4, 0), 0);
    }
};

QTEST_MAIN(P0Test)
#include "test_p0.moc"
