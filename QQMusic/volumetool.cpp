#include "volumetool.h"
#include "ui_volumetool.h"
#include <QGraphicsDropShadowEffect>
#include <QPainter>

VolumeTool::VolumeTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VolumeTool)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

    // 在windows上，设置透明效果后，窗⼝需要加上Qt::FramelessWindowHint格式
    // 否则没有控件位置的背景是⿊⾊的
    // 由于默认窗⼝有阴影，因此还需要将窗⼝的原有的阴影去掉，窗⼝需要加上 Qt::NoDropShadowWindowHint
    setAttribute(Qt::WA_TranslucentBackground);

    // 自定义阴影效果
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setColor("#646464");
    shadowEffect->setOffset(0, 0);
    shadowEffect->setBlurRadius(10);
    this->setGraphicsEffect(shadowEffect);

    // 给按钮设置图标
    ui->silenceBtn->setIcon(QIcon(":/images/volumn.png"));

    // 设置初始音量为20%
    ui->volumeRatio->setText("20%");
    // 设置outSlider尺寸
    QRect rect = ui->outSlider->geometry();
    // 窗体原本高度是180*20%=36, 25是rect距离父元素上方的距离
    ui->outSlider->setGeometry(rect.x(), 180 - 36 + 25, rect.width(), 36);

    // 移动按钮位置
    ui->sliderBtn->move(ui->sliderBtn->x(), ui->outSlider->y() - ui->sliderBtn->height()/2);

}

VolumeTool::~VolumeTool()
{
    delete ui;
}

void VolumeTool::paintEvent(QPaintEvent *event)
{
    (void)event;
    // 绘制volumeTool界面的三角形
    QPainter painter(this); // 指定一个this,让它知道在哪里画
    painter.setRenderHint(QPainter::Antialiasing, true); // 设置抗锯齿

    // 1.设置画笔
    painter.setPen(Qt::NoPen);

    // 2.设置画刷
    painter.setBrush(Qt::white);

    // 3.绘制三角形
    QPolygon polygon;
    QPoint a(10 + 10, 300);
    QPoint b(10 + 10 + 60, 300);
    QPoint c(10 + 10 + 30, 300 + 20);
    polygon.append(a);
    polygon.append(b);
    polygon.append(c);

    painter.drawPolygon(polygon);
}
