#include "commonpage.h"
#include "ui_commonpage.h"
#include "listitembox.h"
#include <QDebug>

CommonPage::CommonPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommonPage)
{
    ui->setupUi(this);
    // 取消水平滚动条
    ui->pageMusicList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // playAllBtn按钮的信号槽处理
    // 当播放按钮点击时，发射playAll信号，播放当前⻚⾯的所有歌曲
    // playAll信号交由QQMusic中处理
    connect(ui->playAllBtn, &QPushButton::clicked, this, [=](){
        emit(playAll(pageType));
    });

    // 鼠标双击后,发射信号告诉QQMusic，播放this⻚⾯中被双击的歌曲
    connect(ui->pageMusicList, &QListWidget::doubleClicked, this, [=](const QModelIndex &index){
        emit(playMusicByindex(this, index.row()));
    });
}

CommonPage::~CommonPage()
{
    delete ui;
}

void CommonPage::setPageType(PageType pageType)
{
    this->pageType = pageType;
}

void CommonPage::setCommonPageUI(const QString &text, const QString &imagePath)
{
    // 设置文本
    ui->PageTittle->setText(text);

    // 设置图片
    ui->musicImageLabel->setPixmap(QPixmap(imagePath));
    ui->musicImageLabel->setScaledContents(true); // 自动适应大小
}

void CommonPage::addMusicToMusicPage(MusicList& musicList)
{
    // 清除 musicListOfPage 和界面的显示是无关的.
    musicListOfPage.clear();
    for(auto& music : musicList)
    {
        switch(pageType)
        {
        case LIKE_PAGE:
            if(music.getIsLike()) musicListOfPage.push_back(music.getMusicId());
            break;
        case LOCAL_PAGE:
            musicListOfPage.push_back(music.getMusicId());
            break;
        case HISTORY_PAGE:
            if(music.getIsHistory()) musicListOfPage.push_back(music.getMusicId());
            break;
        default:
            qDebug() << "暂不支持";
        }
    }
}

void CommonPage::setMusicImage(QPixmap pixmap)
{
    ui->musicImageLabel->setPixmap(pixmap);
    ui->musicImageLabel->setScaledContents(true);
}

void CommonPage::reFresh(MusicList &musicList)
{
    // 每次添加之前我们先将QListWidget之前的内容清空
    ui->pageMusicList->clear();

    // 从musicList中分离出当前⻚⾯的所有⾳乐
    // 添加新的歌曲
    addMusicToMusicPage(musicList);

    // 遍历歌单，将歌单中的歌曲显示到界面
    for(auto& musicId : musicListOfPage)
    {
        auto it = musicList.findMusicById(musicId);
        if(it == musicList.end())
            continue; // 没找到就跳过

        // 将ListItemBox对象放置pageMusicList
        ListItemBox* listItemBox = new ListItemBox(this);
        // 往listitemBox对象上设置歌曲名字，歌手名字，专辑名字
        listItemBox->setMusicName(it->getMusicName());
        listItemBox->setMusicSinger(it->getMusicSinger());
        listItemBox->setMusicAlbum(it->getMusicAlbumn());
        listItemBox->setLikeMusic(it->getIsLike());

        QListWidgetItem* listWidgetItem = new QListWidgetItem(ui->pageMusicList);
        listWidgetItem->setSizeHint(QSize(listItemBox->width(), listItemBox->height())); // 设置成推荐大小(这里是没有的,我们自己设置宽高)
        ui->pageMusicList->setItemWidget(listWidgetItem, listItemBox); // 关联设置起来了

        // 拦截listItemBox的信号,再进行一个中转,发射一个信号到QQMusic中去进行处理
        connect(listItemBox, &ListItemBox::setLike, this, [=](bool isLike)
        {
            emit updateLikeMusic(isLike, it->getMusicId());
        });
    }

    // 触发窗口重绘
    // update(); // update()将paintEvent放入事件循环队列中，不立即处理
    repaint(); // 立即触发

}

void CommonPage::addMusicToPlayList(MusicList &musicList, QMediaPlaylist *playList)
{
    for(auto& music : musicList)
    {
        switch(pageType)
        {
        case LIKE_PAGE:
            if(music.getIsLike()) playList->addMedia(music.getMusicUrl());
            break;
        case LOCAL_PAGE:
            playList->addMedia(music.getMusicUrl());
            break;
        case HISTORY_PAGE:
            if(music.getIsHistory()) playList->addMedia(music.getMusicUrl());
            break;
        default:
             qDebug() << "暂不支持";
        }
    }
}

const QString CommonPage::getMusicIdByindex(int index)
{
    if(index >= musicListOfPage.size())
    {
        qDebug() << "暂不此歌曲";
        return "";
    }

    return musicListOfPage[index];
}

