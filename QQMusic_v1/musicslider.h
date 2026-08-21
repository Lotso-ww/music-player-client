#ifndef MUSICSLIDER_H
#define MUSICSLIDER_H

#include <QWidget>

namespace Ui {
class MusicSlider;
}

class MusicSlider : public QWidget
{
    Q_OBJECT

public:
    explicit MusicSlider(QWidget *parent = nullptr);
    ~MusicSlider();
    void moveSlider(); // 修改outLine的宽度为currentPos;
    void checkCurrentPos(); // 边界检查
    void setStep(float ratio);

signals:
 void setMusicSliderPosition(float);
protected:
    // 采用事件重写的方式来实现(当然也是可以使用事件过滤的)
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    Ui::MusicSlider *ui;
    int currentPos; // 滑动条当前位置
    int maxWidth;
};

#endif // MUSICSLIDER_H
