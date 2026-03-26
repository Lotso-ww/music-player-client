#ifndef VOLUMETOOL_H
#define VOLUMETOOL_H

#include <QWidget>

namespace Ui {
class VolumeTool;
}

class VolumeTool : public QWidget
{
    Q_OBJECT

public:
    explicit VolumeTool(QWidget *parent = nullptr);
    ~VolumeTool();
    void paintEvent(QPaintEvent *event);

    // 计算音量
    // 根据⿏标在滑竿上滑动更新滑动界面，并按照⽐例计算⾳量⼤⼩
    void calculateVolume();

    // 事件过滤器
    bool eventFilter(QObject* object, QEvent* event);

    // 关联静音按钮的槽函数
    void ononSilenceBtnClicked();
signals:
    void setSilence(bool);
    void setMusicVolume(int);
private:
    Ui::VolumeTool *ui;
    bool isMuted;    // 标记是不是禁音
    int volumeRatio; // 标记音量
};

#endif // VOLUMETOOL_H
