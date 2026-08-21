#include "recbox.h"
#include "ui_recbox.h"

#include "recboxitem.h"
#include <QJsonObject>

RecBox::RecBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecBox),
    row(1),
    col(4)
{
    ui->setupUi(this);
}

RecBox::~RecBox()
{
    delete ui;
}

void RecBox::initRecBoxUi(QJsonArray data, int row)
{
    // 如果是两⾏，说明当前RecBox是主界⾯上的supplyMusicBox
    if(2 == row)
    {
        this->row = row;
        col = 8;
    }
    else
    {
        // 否则：只有⼀⾏，为主界⾯上recMusicBox
        ui->recListDown->hide();
    }

    // 图⽚保存起来
    imageList = data;

    // 默认显⽰第0组
     currentIndex = 0;

     // 计算总共有⼏组图⽚
     count = imageList.size()/col ;
    // 往RecBox中添加图⽚
    createRecItem();
}

void RecBox::createRecItem()
{
    // 溢出掉之前的旧元素
    QList<RecBoxItem*> recUpList = ui->recListUp->findChildren<RecBoxItem*>();
    for(auto& e : recUpList)
    {
        ui->recListUpLayout->removeWidget(e);
        delete e;
    }

    QList<RecBoxItem*> recDownList = ui->recListDown->findChildren<RecBoxItem*>();
    for(auto& e : recDownList)
    {
        ui->recListDownLayout->removeWidget(e);
        delete e;
    }

    // 创建RecBoxItem对象，往RecBox里面添加
    // 今日为你推荐 row = 1, col = 4;
    // 音乐补给站: row = 2, col = 8;
    int index = 0; // 方便分今日推荐和音乐补给站的item数量
    for(int i = currentIndex * col; i < col + currentIndex * col; i++)
    {
        RecBoxItem* item = new RecBoxItem();

        // 设置图片和对应文本
        QJsonObject object = imageList[i].toObject();
        item->setRecText(object.value("text").toString());
        item->setRecImage(object.value("path").toString());

        // recMusicBox：col为4，元素添加到ui->recListUpHLayout中
        // supplyMuscBox: col为8， ui->recListUpHLayout添加4个，ui->recListDownHLayout添加4个
        // 即supplyMuscBox上下两⾏都要添加
        // 如果是recMusicBox：row为1，只能执⾏else，所有4个RecBoxItem都添加到ui->recListUpHLayout中
        // 如果是supplyMuscBox：row为2，col为8，col/2结果为4，i为0 1 2 3时，元素添加到ui->recListDownHLayout中
        // i为4 5 6 7时，元素添加到ui->recListUpHLayout中
        if(2 == row && index >= col / 2)
        {
            ui->recListDownLayout->addWidget(item);
        }
        else
        {
            ui->recListUpLayout->addWidget(item);
        }

        index++;
    }
}

void RecBox::on_btDown_clicked()
{
    // 点击按钮，需要显示下一组图片，如果已经是最后一组图⽚，显示第0组图片
    currentIndex++;
    if(currentIndex >= count)
        currentIndex = 0;

    createRecItem();
}

void RecBox::on_btUp_clicked()
{
    // 点击按钮，需要显示上一组图片，如果已经是第0组图片，显示最后一组图片
    currentIndex--;
    if(currentIndex < 0)
        currentIndex = count - 1;

    createRecItem();
}



