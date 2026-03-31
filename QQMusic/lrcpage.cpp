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
}

bool LrcPage::parseLrc(const QString &lrcPath)
{
    // 打开文件
    QFile lrcFile(lrcPath);
    if(!lrcFile.open(QFile::ReadOnly))
    {
        return false; // 打开失败
    }

    while(!lrcFile.atEnd()) // 没读到结尾就继续
    {
        // 读取每一行
        QString word = lrcFile.readLine(1024);

        // [00:17.94]那些失眠的⼈啊 你们还好吗
        // [0:58.600.00]你像⼀只飞来飞去的蝴蝶
        int start = 0, end = 0;
        end = word.indexOf(']', start);
        QString lrcTime = word.mid(start, end - start + 1);
        QString lrcText = word.mid(end + 1); // 第二个不给默认到最后

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

LrcPage::~LrcPage()
{
    delete ui;
}
