#include "lrcpage.h"
#include "ui_lrcpage.h"

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

LrcPage::~LrcPage()
{
    delete ui;
}
