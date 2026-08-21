#include "listitembox.h"
#include "ui_listitembox.h"

ListItemBox::ListItemBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListItemBox),
    isLike(false)
{
    ui->setupUi(this);

    // 连接信号槽
    connect(ui->likeBtn, &QPushButton::clicked, this, &ListItemBox::onLikeBtnClicked);
}

ListItemBox::~ListItemBox()
{
    delete ui;
}

void ListItemBox::setMusicName(const QString& musicName)
{
    ui->musicNameLabel->setText(musicName);
}
void ListItemBox::setMusicSinger(const QString& musicSinger)
{
    ui->musicSingerLabel->setText(musicSinger);
}
void ListItemBox::setMusicAlbum(const QString& musicAlbum)
{
    ui->musicAlbumLabel->setText(musicAlbum);
}

void ListItemBox::setLikeMusic(bool isLike)
{
    this->isLike = isLike;
    if(isLike)
        ui->likeBtn->setIcon(QIcon(":/images/like_2.png"));
    else
        ui->likeBtn->setIcon(QIcon(":/images/like_3.png"));
}

void ListItemBox::onLikeBtnClicked()
{
    isLike = !isLike;
    setLikeMusic(isLike);

    // 发射一个信号, 先在CommonPage进行拦截
    emit setLike(isLike);
}

void ListItemBox::enterEvent(QEvent *event)
{
    (void)event;
    setStyleSheet("background-color:#EFEFEF");

}

void ListItemBox::leaveEvent(QEvent *event)
{
    (void)event;
    setStyleSheet("");
}
