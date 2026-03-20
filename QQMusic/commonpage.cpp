#include "commonpage.h"
#include "ui_commonpage.h"
#include "listitembox.h"
#include <QDebug>

CommonPage::CommonPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommonPage)
{
    ui->setupUi(this);
}

CommonPage::~CommonPage()
{
    delete ui;
}

void CommonPage::setPageType(PageType pageType)
{
    this->pageType = pageType;
}

void CommonPage::addMusicToMusicPage(MusicList musicList)
{
    for(auto& music : musicList)
    {
        switch(pageType)
        {
        case LIKE_PAGE:
            if(music.getISLike()) musicListOfPage.push_back(music.getMusicId());
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

void CommonPage::setCommonPageUI(const QString &text, const QString &imagePath)
{
    // 设置文本
    ui->PageTittle->setText(text);

    // 设置图片
    ui->musicImageLabel->setPixmap(QPixmap(imagePath));
    ui->musicImageLabel->setScaledContents(true); // 自动适应大小

    // 测试
    ListItemBox* listItemBox = new ListItemBox(this);
    QListWidgetItem* listWidgetItem = new QListWidgetItem(ui->pageMusicList);
    listWidgetItem->setSizeHint(QSize(listItemBox->width(), listItemBox->height())); // 设置成推荐大小(这里是没有的,我们自己设置宽高)
    ui->pageMusicList->setItemWidget(listWidgetItem, listItemBox); // 关联设置起来了
}
