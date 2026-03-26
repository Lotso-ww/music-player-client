#include "musicslider.h"
#include "ui_musicslider.h"
#include <QMouseEvent>

MusicSlider::MusicSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicSlider)
{
    ui->setupUi(this);

    // 初始情况下，还没有开始播放，将当前播放进度设置为0
     currentPos = 0;
     maxWidth = width();
     moveSlider();
}

MusicSlider::~MusicSlider()
{
    delete ui;
}

void MusicSlider::moveSlider()
{
    ui->outLine->setGeometry(ui->outLine->x(), ui->outLine->y(), currentPos, ui->outLine->height());
}

void MusicSlider::checkCurrentPos()
{
    // 验证：鼠标点击的x坐标是否越界，如果越界将其调整到边界
    if(currentPos < 0) currentPos = 0;
    if(currentPos > maxWidth) currentPos = maxWidth;
}

void MusicSlider::mouseMoveEvent(QMouseEvent *event)
{
    // 注意：QMouseEvent中的pos()为⿏标相对于widget的坐标，不是相当于screen
    // 因此鼠标位置的 x 坐标可直接作为outLine的宽度
    currentPos = event->pos().x();
    checkCurrentPos();
    moveSlider();

}
void MusicSlider::mousePressEvent(QMouseEvent *event)
{
    // 验证滑动是否在矩形范围里面
    // 如果鼠标不在MusicSlider的矩形内，不进⾏拖拽
    QRect musicSliderRect = QRect(0, 0, geometry().width(), geometry().height());
    if(!musicSliderRect.contains(event->pos()))
    {
        return;
    }

    // 鼠标已经按下才触发
    // 根据鼠标滑动的位置更新outLine的宽度
    if(event->buttons() == Qt::LeftButton)
    {
         currentPos = event->pos().x();
         checkCurrentPos(); // 边界检查

         moveSlider();
    }
}
void MusicSlider::mouseReleaseEvent(QMouseEvent *event)
{
    currentPos = event->pos().x(); // 这里也可以不用再计算一次,但是还是带上
    checkCurrentPos(); // 边界检查
    moveSlider();
}
