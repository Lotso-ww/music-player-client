#include "listitembox.h"
#include "ui_listitembox.h"

ListItemBox::ListItemBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListItemBox)
{
    ui->setupUi(this);
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
