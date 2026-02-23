#include "qqmusic.h"
#include "ui_qqmusic.h"

QQMusic::QQMusic(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QQMusic)
{
    ui->setupUi(this);
}

QQMusic::~QQMusic()
{
    delete ui;
}

