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
}


void QQMusic::on_quit_clicked()
{
    close();
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


