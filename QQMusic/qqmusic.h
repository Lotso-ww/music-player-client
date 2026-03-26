#ifndef QQMUSIC_H
#define QQMUSIC_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "commonpage.h"
#include "musiclist.h"
#include "volumetool.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QQMusic; }
QT_END_NAMESPACE

class QQMusic : public QWidget
{
    Q_OBJECT

public:
    QQMusic(QWidget *parent = nullptr);
    ~QQMusic();

    void initUI();   // 初始化UI界面
    void initPlayer(); // 媒体播放和控制相关初始化
    void connectSignalAndSlots();
    QJsonArray randomPicture();

    void updateLikeMusicAndPage(bool isLike, const QString& musicId);// 响应CommonPage发射的updateLikeMusic信号
private slots:
    void on_quit_clicked();
    void on_btForm_clicked(int pageId);
    void on_volume_clicked();

    void on_addLocal_clicked();

    // 媒体播放相关槽函数
    // 播放按钮: 歌曲在播放和暂停之间切换
    void onPlayMusic();

    // 播放上一曲
    void onPlayUpClicked();
    // 播放下一曲
    void onPlayDownClicked();

    // 切换播放模式
    void onPlaybackModeClicked();

    // QMediaPlayer -- stateChanged信号处理
    // 播放状态发⽣改变、
    void onPlayStateChanged();
    // 播放列表模式发生改变
    void onPlaybackModeChanged(QMediaPlaylist::PlaybackMode playbackMode); // 带不带参数其实都行,上面没带这个就带一下

    // 处理播放所有的信号对应的槽函数
    void onPlayAll(PageType pageType);
    void playAllOfCommonPage(CommonPage* page, int index);
    void onPlayMusicByIndex(CommonPage* page, int index);
    // ⽀持播放历史记录
    void onPlayCurrentIndexChanged(int index);

    // 关联禁音信号的槽函数(volumetool)
    void setMusicSilence(bool isMuted);
    // 设置音量
    void setMusicVolume(int volume);

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);

private:
    Ui::QQMusic *ui;
    QPoint dragPosition;
    MusicList musicList; // 程序中组织管理的音乐列表
    VolumeTool *volumeTool;

    QMediaPlayer* player;     // 媒体播放控制
    QMediaPlaylist* playList; // 要多⾸歌曲播放，以及更复杂的播放设置，需要给播放器设置媒体列表

    CommonPage* currentPage; // 记录当前播放界面
};
#endif // QQMUSIC_H
