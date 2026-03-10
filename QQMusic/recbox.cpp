#include "recbox.h"
#include "ui_recbox.h"

#include "recboxitem.h"

RecBox::RecBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecBox),
    row(1),
    col(4)
{
    ui->setupUi(this);
    RecBoxItem* item = new RecBoxItem();
    ui->recListUpLayout->addWidget(item);
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
    // 往RecBox中添加图⽚
//    createRecItem();
}
