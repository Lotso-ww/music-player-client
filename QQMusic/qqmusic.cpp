#include "qqmusic.h"
#include "ui_qqmusic.h"
#include <QDebug>
#include <QPushButton>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QJsonArray>
#include <QJsonObject>
#include <QFileDialog>
#include <QDial>

QQMusic::QQMusic(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QQMusic)
{
    ui->setupUi(this);

    initUI();
    initPlayer();
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

    // 本地下载btForm默认显示动画
    ui->local->showAnimat();
    ui->stackedWidget->setCurrentIndex(4);

    // 初始化推荐页面
    srand((unsigned int)time(nullptr)); // 设置随机数种子确保每次启动的图片顺序都是不同的
    ui->recMusicBox->initRecBoxUi(randomPicture(), 1);
    ui->supplyMusicBox->initRecBoxUi(randomPicture(), 2);

    // 设置CommonPage的文本和图标
    ui->likePage->setPageType(PageType::LIKE_PAGE);
    ui->likePage->setCommonPageUI("我喜欢", ":/images/ilikebg.png");

    ui->localPage->setPageType(PageType::LOCAL_PAGE);
    ui->localPage->setCommonPageUI("本地下载", ":/images/localbg.png");

    ui->recentPage->setPageType(PageType::HISTORY_PAGE);
    ui->recentPage->setCommonPageUI("最近播放", ":/images/recentbg.png");

    // 按钮的背景图⽚样式去除掉之后，需要设置默认图标
    // 播放控制区按钮图标设定
    ui->play->setIcon(QIcon(":/images/play3.png"));          // 默认为暂停图标
    ui->playMode->setIcon(QIcon(":/images/shuffle_2.png"));  // 默认为随机播放

    // 创建⾳量调节窗⼝对象并挂到对象树
    volumeTool = new VolumeTool(this);
}

void QQMusic::initPlayer()
{
    // 1. 初始化媒体播放器和播放列表
    player = new QMediaPlayer(this);
    playList = new QMediaPlaylist(this);

    // 2. 设置默认播放模式 -- 默认列表循环播放
    playList->setPlaybackMode(QMediaPlaylist::Random);

    // 3. 将播放列表设置进媒体播放器
    player->setPlaylist(playList);

    // 4. 设置默认音量 -- 默认20%
    player->setVolume(20);

    // 播放状态改变的槽函数关联
    connect(player, &QMediaPlayer::stateChanged, this, &QQMusic::onPlayStateChanged);

    // 播放列表模式改变的槽函数关联
    connect(playList, &QMediaPlaylist::playbackModeChanged, this, &QQMusic::onPlaybackModeChanged);

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

    // 关联CommonPage发射的updateLikeMusic信号,三个页面都需要
    connect(ui->likePage, &CommonPage::updateLikeMusic, this, &QQMusic::updateLikeMusicAndPage);
    connect(ui->localPage, &CommonPage::updateLikeMusic, this, &QQMusic::updateLikeMusicAndPage);
    connect(ui->recentPage, &CommonPage::updateLikeMusic, this, &QQMusic::updateLikeMusicAndPage);

    // 播放控制器相关槽函数关联
    connect(ui->play, &QPushButton::clicked, this, &QQMusic::onPlayMusic);
    connect(ui->playUp, &QPushButton::clicked, this, &QQMusic::onPlayUpClicked);
    connect(ui->playDown, &QPushButton::clicked, this, &QQMusic::onPlayDownClicked);
    connect(ui->playMode, &QPushButton::clicked, this, &QQMusic::onPlaybackModeClicked);

    // 关联三个页面播放所有的信号和槽函数
    connect(ui->likePage, &CommonPage::playAll, this, &QQMusic::onPlayAll);
    connect(ui->localPage, &CommonPage::playAll, this, &QQMusic::onPlayAll);
    connect(ui->recentPage, &CommonPage::playAll, this, &QQMusic::onPlayAll);

    // 关联三个页面中ListItemBox双击
    connect(ui->likePage, &CommonPage::playMusicByindex, this, &QQMusic::onPlayMusicByIndex);
    connect(ui->localPage, &CommonPage::playMusicByindex, this, &QQMusic::onPlayMusicByIndex);
    connect(ui->recentPage, &CommonPage::playMusicByindex, this, &QQMusic::onPlayMusicByIndex);
}

// 设置随机图⽚【歌曲的图⽚】
QJsonArray QQMusic::randomPicture()
{
    // 推荐文本 + 推荐图片
    QVector<QString> vecImageName;
    // 支持流插入
    vecImageName<< "001.png" << "003.png" << "004.png" << "005.png" << "006.png" << "007.png"
                << "008.png" << "009.png" << "010.png" << "011.png" << "012.png" << "013.png"
                << "014.png" << "015.png" << "016.png" << "017.png" << "018.png" << "019.png"
                << "020.png" << "021.png" << "022.png" << "023.png" << "024.png" << "025.png"
                << "026.png" << "027.png" << "028.png" << "029.png" << "030.png" << "031.png"
                << "032.png" << "033.png" << "034.png" << "035.png" << "036.png" << "037.png"
                << "038.png" << "039.png" << "040.png";
   std::random_shuffle(vecImageName.begin(), vecImageName.end());

   // 001.png
   // path: ":/images/rec/"+vecImageName[i];
   // text: "推荐-001"
   QJsonArray objArray;
   for(int i = 0; i < vecImageName.size(); i++)
   {
       QJsonObject obj;
       obj.insert("path", ":/images/rec/" + vecImageName[i]);

       // arg(i, 3, 10, QCchar('0'))
       // i：要放⼊%1位置的数据
       // 3: 三位数
       // 10：表⽰⼗进制数
       // QChar('0')：数字不够三位，前⾯⽤字符'0'填充
       QString strText = QString("推荐-%1").arg(i, 3, 10, QChar('0'));
       obj.insert("text", strText);

       objArray.append(obj);
   }

   return objArray;
}

void QQMusic::updateLikeMusicAndPage(bool isLike, const QString &musicId)
{
    // 1. 找到歌曲，并更新对应Music对象信息
    auto it = musicList.findMusicById(musicId);
    if(it != musicList.end())
    {
        it->setIsLike(isLike);
    }

    //2. 通知三个页面更新自己的数据
    ui->likePage->reFresh(musicList);
    ui->localPage->reFresh(musicList);
    ui->recentPage->reFresh(musicList);
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
            btItem->hideAnimat();
        }
        else
        {
            btItem->showAnimat();
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



void QQMusic::on_volume_clicked()
{
    // 1. 获取ui->volume控件的left-top坐标，并转换为基于屏幕的全局坐标
    QPoint point = ui->volume->mapToGlobal(QPoint(0,0)); // 给 0,0坐标就行，该函数会自己生成基于全局的

    // 2. 计算volumeTool需要移动到的位置，即ui->volume正上方左边偏一半
    QPoint volumeLeftTop = point - QPoint(volumeTool->width() / 2, volumeTool->height());

    // 对volumeTool进行微调
    volumeLeftTop.setX(volumeLeftTop.x() + 15);
    volumeLeftTop.setY(volumeLeftTop.y() + 30);
    // 3. 移动volumeTool
    volumeTool->move(volumeLeftTop);
    volumeTool->show();
}

void QQMusic::on_addLocal_clicked()
{
    // 1. 创建一个文件对话框,并且设置标题
    QFileDialog* fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("添加本地音乐");

    // 2. 设置对话框的打开格式和选择文件的模式
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen); // 设置一个打开格式的文件对话框
    fileDialog->setFileMode(QFileDialog::ExistingFiles); // 设置只能选择文件，并且⼀次性可以选择多个存在的文件; 可以一次打开多个

    // 3. 设置对话框的MIME过滤器
    QStringList mimeTypeFilters;
    mimeTypeFilters << "application/octet-stream";
    fileDialog->setMimeTypeFilters(mimeTypeFilters);

    // 4. 设置对话框打开的默认路径，先获取当前工作目录并且进行调整
    QDir dir(QDir::currentPath());
    dir.cdUp();
    QString projectPath = dir.path();
    projectPath += "/QQMusic/musics/";
    fileDialog->setDirectory(projectPath);

    // 5. 显⽰对话框，并接收返回值
    // 模态对话框, exec内部是死循环处理
    if(QDialog::Accepted == fileDialog->exec())
    {
        // 获取选中的文件
        QList<QUrl> fileUrls = fileDialog->selectedUrls();

        // fileUrls: 内部存放的是刚刚选中的文件的url路径
        // 需要将文件信息填充到本地下载

        // 将所有音乐添加到音乐列表中, MusicList
        musicList.addMusicByUrl(fileUrls);

        // 切换到本地⾳乐界面，加载完的音乐需要在此界面上显示
        ui->stackedWidget->setCurrentIndex(4);
        ui->localPage->reFresh(musicList);

        // 添加歌曲到播放列表
        ui->localPage->addMusicToPlayList(musicList, playList);
    }

}

void QQMusic::onPlayMusic()
{
    // 图标切换我们可以在这里实现,但是利用信号更加清晰
    if(QMediaPlayer::StoppedState == player->state())
    {
        // 默认为停止状态,按下按钮后变成播放
        player->play();
    }
    else if(QMediaPlayer::PlayingState == player->state())
    {
        // 处于播放状态,按一下变成暂停
        player->pause();
    }
    else if(QMediaPlayer::PausedState == player->state())
    {
        // 处于暂停状态,按一下变成播放
        player->play();
    }
    else
    {
        qDebug() << player->errorString();
    }
}

void QQMusic::onPlayUpClicked()
{
    playList->previous();
}

void QQMusic::onPlayDownClicked()
{
    playList->next();
}

void QQMusic::onPlaybackModeClicked()
{
    // 1. 根据当前模式切换到下一个模式
    // 2. 设置ToolTip提示
    // 列表循环 -> 随机播放 -> 单曲循环
    // 状态发生改变时,修改图标(这个我们还是通过信号实现)
    if(QMediaPlaylist::Loop == playList->playbackMode())
    {
        // 列表循环 -> 随机播放
        playList->setPlaybackMode(QMediaPlaylist::Random);
        ui->playMode->setToolTip("随机播放");
    }
    else if(QMediaPlaylist::Random == playList->playbackMode())
    {
        // 随机播放 -> 单曲循环
        playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        ui->playMode->setToolTip("单曲循环");
    }
    else if(QMediaPlaylist::CurrentItemInLoop == playList->playbackMode())
    {
        // 单曲循环 -> 列表循环
        playList->setPlaybackMode(QMediaPlaylist::Loop);
        ui->playMode->setToolTip("列表循环");
    }
    else
    {
        qDebug() << "模式暂不支持";
    }
}

void QQMusic::onPlayStateChanged()
{
    if(QMediaPlayer::PlayingState == player->state())
    {
        // 播放状态
        ui->play->setIcon(QIcon(":/images/play_on.png"));
    }
    else
    {
        // 暂停状态
        ui->play->setIcon(QIcon(":/images/play3.png"));
    }
}

void QQMusic::onPlaybackModeChanged(QMediaPlaylist::PlaybackMode playbackMode)
{
    if(QMediaPlaylist::Loop == playbackMode)
    {
        ui->playMode->setIcon(QIcon(":/images/list_play.png"));
    }
    else if(QMediaPlaylist::Random == playbackMode)
    {
        ui->playMode->setIcon(QIcon(":/images/shuffle_2.png"));
    }
    else if(QMediaPlaylist::CurrentItemInLoop == playbackMode)
    {
        ui->playMode->setIcon(QIcon(":/images/single_play.png"));
    }
    else
    {
        qDebug() << "暂不支持";
    }
}

void QQMusic::onPlayAll(PageType pageType)
{
    CommonPage* page = ui->localPage;
    switch(pageType)
    {
    case PageType::LIKE_PAGE:
        page = ui->likePage;
        break;
    case PageType::LOCAL_PAGE:
        page = ui->localPage;
        break;
    case PageType::HISTORY_PAGE:
        page = ui->recentPage;
        break;
   default:
        qDebug() << "暂不支持,待扩展";
    }

    // 从当前页面的0号开始播放
    playAllOfCommonPage(page, 0);
}

void QQMusic::playAllOfCommonPage(CommonPage *page, int index)
{
    // 播放page所在⻚⾯的⾳乐
    // 将播放列表先清空，否则⽆法播放当前CommonPage⻚⾯的歌曲
    // 另外：该页面音乐不⼀定就在播放列表中，因此需要先将该页面音乐添加到播放列表
    playList->clear();

    // 将当前页面歌曲添加到播放列表
    page->addMusicToPlayList(musicList, playList);

    // 设置当前页面列表的播放索引
    playList->setCurrentIndex(index);

    // 开始播放
    player->play();
}

void QQMusic::onPlayMusicByIndex(CommonPage *page, int index)
{
    playAllOfCommonPage(page, index);
}
