#include "qqmusic.h"
#include "ui_qqmusic.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>

QQMusic::QQMusic(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QQMusic)
{
    ui->setupUi(this);

    initUI();
    connectSignalAndSlots();
}

QQMusic::~QQMusic()
{
    delete ui;
}

void QQMusic::initUI()
{
    this->setWindowFlag(Qt::FramelessWindowHint);

    // 实现窗口阴影效果之前需要先设置窗口背景透明
    setAttribute(Qt::WA_TranslucentBackground);

    // 实现窗口阴影效果
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0,0);
    shadowEffect->setColor("#000000"); // 黑色
    shadowEffect->setBlurRadius(20);
    this->setGraphicsEffect(shadowEffect);

    // 设置bodyLeft中6个btForm的图标和文本（调用我们自己实现的函数）
    ui->rec->setIconAndText(":/images/rec.png", "推荐", 0);
    ui->radio->setIconAndText(":/images/radio.png", "电台", 1);
    ui->music->setIconAndText(":/images/music.png", "音乐馆", 2);
    ui->like->setIconAndText(":/images/like.png", "我喜欢", 3);
    ui->local->setIconAndText(":/images/local.png", "本地下载", 4);
    ui->recent->setIconAndText(":/images/recent.png", "最近播放", 5);
}

void QQMusic::connectSignalAndSlots()
{
    // 关联btForm的信号和处理这个信号的槽函数
    connect(ui->rec, &btForm::btClick, this, &QQMusic::on_btForm_clicked);
    connect(ui->radio, &btForm::btClick, this, &QQMusic::on_btForm_clicked);
    connect(ui->music, &btForm::btClick, this, &QQMusic::on_btForm_clicked);
    connect(ui->like, &btForm::btClick, this, &QQMusic::on_btForm_clicked);
    connect(ui->local, &btForm::btClick, this, &QQMusic::on_btForm_clicked);
    connect(ui->recent, &btForm::btClick, this, &QQMusic::on_btForm_clicked);
}

void QQMusic::on_quit_clicked()
{
    close();
}

void QQMusic::on_btForm_clicked(int pageId)
{
    // 1.获取当前⻚⾯所有btFrom按钮类型的对象
    QList<btForm*> btList = this->findChildren<btForm*>();

    // 2.遍历所有 BtForm 对象，将 pageId 与当前点击 ID 不符的按钮都调用 clearBg() 清除样式
    for(auto& btItem : btList)
    {
        if(btItem->getPageId() != pageId)
        {
            btItem->clearBg();
        }
    }

    // 3.设置当前显示页面
    ui->stackedWidget->setCurrentIndex(pageId);
}

void QQMusic::mousePressEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->button())
    {
        dragPosition = event->globalPos() - geometry().topLeft();
        return;
    }
    // 自己关心的处理完之后其他的交给父类来处理
    QWidget::mousePressEvent(event);
}

void QQMusic::mouseMoveEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->buttons())
    {
        move(event->globalPos() - dragPosition);
        return;
    }
    QWidget::mouseMoveEvent(event);
}


