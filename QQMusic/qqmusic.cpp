#include "qqmusic.h"
#include "ui_qqmusic.h"
#include <QMouseEvent>

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
    }
}

void QQMusic::mouseMoveEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->buttons())
    {
        move(event->globalPos() - dragPosition);
    }
}


