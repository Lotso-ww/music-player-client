#include "lrcpage.h"
#include "ui_lrcpage.h"
#include <QFile>
#include <QDebug>
#include <QRegularExpression>
#include <algorithm>

LrcPage::LrcPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LrcPage)
{
    ui->setupUi(this);

    // 设置窗口无标题栏
    setWindowFlag(Qt::FramelessWindowHint);

    // 窗口下移动画
    animal = new QPropertyAnimation(this, "geometry", this);
    animal->setDuration(500);
    animal->setStartValue(QRect(10, 10, width(), height())); // 不用指定都是当前界面的宽高
    animal->setEndValue(QRect(10, 10 + height(), width(), height()));

    // 关联hideBtn,点击动画启动
    connect(ui->hideBtn, &QPushButton::clicked, this, [=]{
       animal->start();
    });

    // 动画结束之后隐藏当前窗口
    connect(animal, &QPropertyAnimation::finished, this, [=]{
       hide();
    });

    showLrcWord(-1);
}

void LrcPage::setMusicNameAndSinger(QString &musicName, QString &musicSigner)
{
    ui->musicName->setText(musicName);
    ui->musicSinger->setText(musicSigner);
}

bool LrcPage::parseLrc(const QString &lrcPath)
{
    lrcLines.clear();
    // 打开文件
    QFile lrcFile(lrcPath);
    if(!lrcFile.open(QFile::ReadOnly))
    {
        showLrcWord(-1);
        return false;
    }

    while(!lrcFile.atEnd()) // 没读到结尾就继续
    {
        // 读取每一行
        QString word = lrcFile.readLine(1024);

        // [00:17.94]那些失眠的⼈啊 你们还好吗
        // [0:58.600.00]你像⼀只飞来飞去的蝴蝶
        const QRegularExpressionMatchIterator matches =
            QRegularExpression("\\[(\\d{1,3}):(\\d{1,2})(?:\\.(\\d{1,3})(?:\\.\\d{1,3})?)?\\]").globalMatch(word);
        const int textStart = word.lastIndexOf(']') + 1;
        const QString lrcText = textStart > 0 ? word.mid(textStart).trimmed() : QString();
        for (auto it = matches; it.hasNext();) {
            const QRegularExpressionMatch match = it.next();
            const int minutes = match.captured(1).toInt();
            const int seconds = match.captured(2).toInt();
            if (seconds >= 60) continue;
            QString fraction = match.captured(3);
            while (fraction.size() < 3) fraction.append('0');
            lrcLines.push_back(LineWordLine(minutes * 60000LL + seconds * 1000LL + fraction.left(3).toInt(), lrcText));
        }
    }

    std::sort(lrcLines.begin(), lrcLines.end(), [](const LineWordLine &left, const LineWordLine &right) {
        return left._wordTime < right._wordTime;
    });

    for(auto& e : lrcLines)
    {
        qDebug() << e._wordTime << ":" << e._wordText;
    }
    if (lrcLines.isEmpty()) showLrcWord(-1);
    return !lrcLines.isEmpty();
}

void LrcPage::showLrcWord(qint64 time)
{
    // 1. 先拿到对应的下标索引
    int index = getWordIndex(time);

    // 2. 显示歌词
    if(-1 == index)
    {
        ui->line1->setText("");
        ui->line2->setText("");
        ui->line3->setText("");
        ui->lineCenter->setText("该歌曲暂无歌词");
        ui->line4->setText("");
        ui->line5->setText("");
        ui->line6->setText("");
    }
    else
    {
        ui->line1->setText(getLrcWordByIndex(index - 3));
        ui->line2->setText(getLrcWordByIndex(index - 2));
        ui->line3->setText(getLrcWordByIndex(index - 1));
        ui->lineCenter->setText(getLrcWordByIndex(index));
        ui->line4->setText(getLrcWordByIndex(index + 1));
        ui->line5->setText(getLrcWordByIndex(index + 2));
        ui->line6->setText(getLrcWordByIndex(index + 3));
    }
}

int LrcPage::getWordIndex(qint64 pos)
{
    // 将时间和歌词时间进行对比
    // 如果没歌词文件显示不了
    if(lrcLines.isEmpty()) return -1;

    if(pos <= lrcLines[0]._wordTime) return 0;

    for(int i = 1; i < lrcLines.size(); i++)
    {
        // 如果在i-1和i之间证明上一次的还没播放完
        if(pos >= lrcLines[i - 1]._wordTime && pos < lrcLines[i]._wordTime)
        {
            return i - 1;
        }
    }

    return lrcLines.size() - 1; // 一直显示的最后一个歌词
}

QString LrcPage::getLrcWordByIndex(int index)
{
    if(index < 0 || index >= lrcLines.size())
    {
        return "";
    }

    return lrcLines[index]._wordText;
}

LrcPage::~LrcPage()
{
    delete ui;
}
