#include "btform.h"
#include "ui_btform.h"

btForm::btForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::btForm)
{
    ui->setupUi(this);

    // 设置line1的动画效果
    line1Animat = new QPropertyAnimation(ui->line1, "geometry", this);
    line1Animat->setDuration(1500);
    line1Animat->setKeyValueAt(0, QRect(7, 25, 2, 0));
    line1Animat->setKeyValueAt(0.5, QRect(7, 10, 2, 15));
    line1Animat->setKeyValueAt(1, QRect(7, 25, 2, 0));
    line1Animat->setLoopCount(-1);
    line1Animat->start();

    // 设置line2的动画效果
    line2Animat = new QPropertyAnimation(ui->line2, "geometry", this);
    line2Animat->setDuration(1600);
    line2Animat->setKeyValueAt(0, QRect(16, 25, 2, 0));
    line2Animat->setKeyValueAt(0.5, QRect(16, 10, 2, 15));
    line2Animat->setKeyValueAt(1, QRect(16, 25, 2, 0));
    line2Animat->setLoopCount(-1);
    line2Animat->start();

    // 设置line3的动画效果
    line3Animat = new QPropertyAnimation(ui->line3, "geometry", this);
    line3Animat->setDuration(1700);
    line3Animat->setKeyValueAt(0, QRect(25, 25, 2, 0));
    line3Animat->setKeyValueAt(0.5, QRect(25, 10, 2, 15));
    line3Animat->setKeyValueAt(1, QRect(25, 25, 2, 0));
    line3Animat->setLoopCount(-1);
    line3Animat->start();

    // 设置line4的动画效果
    line4Animat = new QPropertyAnimation(ui->line4, "geometry", this);
    line4Animat->setDuration(1800);
    line4Animat->setKeyValueAt(0, QRect(34, 25, 2, 0));
    line4Animat->setKeyValueAt(0.5, QRect(34, 10, 2, 15));
    line4Animat->setKeyValueAt(1, QRect(34, 25, 2, 0));
    line4Animat->setLoopCount(-1);
    line4Animat->start();
}

btForm::~btForm()
{
    delete ui;
}

void btForm::setIconAndText(const QString &btIconUrl, const QString &btText, int pageId)
{
    // 设置图标
    ui->btIcon->setPixmap(QPixmap(btIconUrl));

    // 设置文本
    ui->btText->setText(btText);

    // 将按钮和QQMusic中的界面进行关联
    this->pageId = pageId;
}

int btForm::getPageId() const
{
    return pageId;
}

void btForm::clearBg()
{
    // 把背景颜色设置还原成按下之前的
    ui->btStyle->setStyleSheet("#btStyle:hover{background-color:#D8D8D8;}");
}

void btForm::mousePressEvent(QMouseEvent *event)
{
    // 1. 当按钮按下之后，需要修改其背景颜色
    ui->btStyle->setStyleSheet("#btStyle { background-color:rgb(30, 206, 154); }");

    // 2. 当按钮按下之后，需要切换bodyRight中的page页面
    emit btClick(pageId); // 发射信号
}
