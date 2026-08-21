#include "volumetool.h"
#include "ui_volumetool.h"
#include <QGraphicsDropShadowEffect>
#include <QPainter>

VolumeTool::VolumeTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VolumeTool),
    isMuted(false), // 默认静⾳
    volumeRatio(20) // 默认20%
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

    // 关联静⾳按钮的信号槽
    connect(ui->silenceBtn, &QPushButton::clicked, this, &VolumeTool::ononSilenceBtnClicked);

    // 安装事件过滤器
    ui->volumeBox->installEventFilter(this);
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

void VolumeTool::calculateVolume()
{
    // 1. 将鼠标的位置转换为相对坐标，此处只要获取y坐标
    int height = ui->volumeBox->mapFromGlobal(QCursor().pos()).y();

    // 2. 检查height的合法性【25, 25 + 180】
    // ⿏标在volumeBox中可移动的y范围在[25, 205]之间
    height = height < 25 ? 25 : height;
    height = height > 205 ? 205 : height;

    // 3. 更新outSlider的位置和大小, 205是因为我们算的时候是有上面的缝隙的
    ui->outSlider->setGeometry(ui->outSlider->x(), height, ui->outSlider->width(), 205 - height);

    // 4. 移动sliderBtn的位置
    ui->sliderBtn->move(ui->sliderBtn->x(), height - ui->sliderBtn->height() / 2);

    // 5. 计算音量的比例
    volumeRatio = (int)(ui->outSlider->height() / (float)180 * 100);

    // 6. 设置给label显示出来
    ui->volumeRatio->setText(QString::number(volumeRatio) + "%");
}

bool VolumeTool::eventFilter(QObject *object, QEvent *event)
{
    // 过滤volumeBox上的事件
    if(object == ui->volumeBox)
    {
        if(event->type() == QEvent::MouseButtonPress) // 鼠标按下事件
        {
            // 如果是鼠标按下事件，修改sliderBtn和outLine的位置，并计算volumeRatio
            calculateVolume();
        }
        else if(event->type() == QEvent::MouseButtonRelease) // 鼠标释放
        {
            // 如果是鼠标释放事件，直接发射setMusicVolume信号
            emit(setMusicVolume(volumeRatio));
        }
        else if(event->type() == QEvent::MouseMove) // 鼠标滚动事件
        {
            // 重新计算并且发射信号
            calculateVolume();
            emit(setMusicVolume(volumeRatio));
        }

        return true;
    }
    return QObject::eventFilter(object, event);
}

void VolumeTool::ononSilenceBtnClicked()
{
    isMuted = !isMuted;
    if(isMuted)
    {
        // true: 静音
        ui->silenceBtn->setIcon(QIcon(":/images/silent.png"));
    }
    else
    {
        // false: 非禁音
        ui->silenceBtn->setIcon(QIcon(":/images/volumn.png"));
    }

    // 向QQMusic发射信号
    emit setSilence(isMuted);
}
