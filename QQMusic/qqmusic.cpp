#include "qqmusic.h"
#include "ui_qqmusic.h"

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
