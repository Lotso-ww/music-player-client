#include "btform.h"
#include "ui_btform.h"

btForm::btForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::btForm)
{
    ui->setupUi(this);
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

void btForm::mousePressEvent(QMouseEvent *event)
{
    // 1. 当按钮按下之后，需要修改其背景颜色
    ui->btStyle->setStyleSheet("#btStyle { background-color:rgb(30, 206, 154); }");

    // 2. 当按钮按下之后，需要切换bodyRight中的page页面
    emit btClick(pageId); // 发射信号
}
