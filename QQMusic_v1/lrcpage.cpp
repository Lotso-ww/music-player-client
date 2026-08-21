#include "lrcpage.h"
#include "ui_lrcpage.h"
#include <QFile>
#include <QDebug>

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
    // 打开文件
    QFile lrcFile(lrcPath);
    if(!lrcFile.open(QFile::ReadOnly))
    {
        return false; // 打开失败
    }

    // 清除上一首歌曲的歌词
    lrcLines.clear();

    while(!lrcFile.atEnd()) // 没读到结尾就继续
    {
        // 读取每一行
        QString word = lrcFile.readLine(1024);

        // [00:17.94]那些失眠的⼈啊 你们还好吗
        // [0:58.600.00]你像⼀只飞来飞去的蝴蝶
        int start = 0, end = 0;
        end = word.indexOf(']', start);
        QString lrcTime = word.mid(start, end - start + 1);
        QString lrcText = word.mid(end + 1, word.size() - end - 2);

        // 解析时间 -- ms
        // [00:17.94] [0:58.600.00]
        qint64 lineTime = 0;
        // 解析分 -- 并转成ms
        start = 1, end = 0;
        end = word.indexOf(':', start);
        lineTime += lrcTime.mid(start, end - start).toLong()*60*1000;

        // 解析秒 -- 并转成ms
        start = end + 1;
        end = word.indexOf('.', start);
        lineTime += lrcTime.mid(start, end - start).toLong()*1000;

        // 解析ms
        start = end + 1;
        end = word.indexOf('.', start);// 没找到的话会也是会到结尾
        lineTime += lrcTime.mid(start, end - start).toLong();

        // 将这一行保存
        lrcLines.push_back(LineWordLine(lineTime, lrcText));
    }

    for(auto& e : lrcLines)
    {
        qDebug() << e._wordTime << ":" << e._wordText;
    }
    return true;
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
