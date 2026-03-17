#include "volumetool.h"
#include "ui_volumetool.h"
#include <QGraphicsDropShadowEffect>

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
}

VolumeTool::~VolumeTool()
{
    delete ui;
}
