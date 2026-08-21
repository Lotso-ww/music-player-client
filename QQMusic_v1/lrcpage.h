#ifndef LRCPAGE_H
#define LRCPAGE_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QVector>

// 其实用pair也可以
struct LineWordLine{
  LineWordLine(qint64 wordTime, QString wordText)
      :_wordTime(wordTime)
      ,_wordText(wordText)
  {}
  qint64 _wordTime;   // 时间
  QString _wordText;  // 歌词内容
};

namespace Ui {
class LrcPage;
}

class LrcPage : public QWidget
{
    Q_OBJECT

public:
    explicit LrcPage(QWidget *parent = nullptr);
    void setMusicNameAndSinger(QString &musicName, QString &musicSigner);
    bool parseLrc(const QString& lrcPath);
    void showLrcWord(qint64 time);
    int getWordIndex(qint64 pos);
    QString getLrcWordByIndex(int index);
    ~LrcPage();
private:
    Ui::LrcPage *ui;
    QPropertyAnimation* animal;
    QVector<LineWordLine> lrcLines; // 按照时间的先后次序保存每⾏歌词
};

#endif // LRCPAGE_H
