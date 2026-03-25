#ifndef COMMONPAGE_H
#define COMMONPAGE_H

#include <QWidget>
#include <QMediaPlaylist>
#include "musiclist.h"

namespace Ui {
class CommonPage;
}

// 通过枚举: 区分不同的Page页面
enum PageType
{
    LIKE_PAGE,    // 我喜欢界面
    LOCAL_PAGE,   // 本地下载界面
    HISTORY_PAGE  // 历史播放界面
};


class CommonPage : public QWidget
{
    Q_OBJECT

public:
    explicit CommonPage(QWidget *parent = nullptr);
    ~CommonPage();

    void setPageType(PageType pageType);
    void setCommonPageUI(const QString& text, const QString& imagePath);
    void addMusicToMusicPage(MusicList& musicList);
    void reFresh(MusicList& musicList);

    void addMusicToPlayList(MusicList& musicList, QMediaPlaylist* playList);
signals:
    void updateLikeMusic(bool isLike, const QString& musicId);
    // 下面这两个信号发送QQMusic处理
    void playAll(PageType pageType);
    void playMusicByindex(CommonPage*, int); // 可以这样写也可以像上面一样
private:
    Ui::CommonPage *ui;
    PageType pageType; // 标记属于likePage、localPage、recentPage哪个页面
    QVector<QString> musicListOfPage; // 具体某个页面的⾳乐，将来只需要存储音乐的id即可
};

#endif // COMMONPAGE_H
