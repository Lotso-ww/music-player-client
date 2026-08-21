#include "recboxitem.h"
#include "ui_recboxitem.h"

#include <QPropertyAnimation>

RecBoxItem::RecBoxItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecBoxItem)
{
    ui->setupUi(this);

    // 注意：不要忘记事件拦截器安装，否则时间拦截不到，因此需要在构造函数中添加：
    // 拦截事件处理器时，⼀定要安装事件拦截器
    ui->musicImageBox->installEventFilter(this);
}

RecBoxItem::~RecBoxItem()
{
    delete ui;
}

bool RecBoxItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->musicImageBox)
    {
        if(event->type() == QEvent::Enter)
        {
            // 鼠标进入,触发的向上的动画
            QPropertyAnimation* animat = new QPropertyAnimation(ui->musicImageBox, "geometry"); // 我们不挂在对象树上
            animat->setDuration(150);
            animat->setStartValue(QRect(9, 9, ui->musicImageBox->width(), ui->musicImageBox->height()));
            animat->setEndValue(QRect(9, 0, ui->musicImageBox->width(), ui->musicImageBox->height()));
            animat->start();

            // 因为这里的动画不是一直持续存在的,我们需要自己手动释放
            // 注意：动画结束的时候会触发finished信号，拦截到该信号，销毁animation
            connect(animat, &QPropertyAnimation::finished, this, [=]()
            {
                delete animat;
            });
        }
        else if(event->type() == QEvent::Leave)
        {
            // 鼠标离开,触发的向下的动画
            QPropertyAnimation* animat = new QPropertyAnimation(ui->musicImageBox, "geometry"); // 我们不挂在对象树上
            animat->setDuration(150);
            animat->setStartValue(QRect(9, 0, ui->musicImageBox->width(), ui->musicImageBox->height()));
            animat->setEndValue(QRect(9, 9, ui->musicImageBox->width(), ui->musicImageBox->height()));
            animat->start();

            // 因为这里的动画不是一直持续存在的,我们需要自己手动释放
            // 注意：动画结束的时候会触发finished信号，拦截到该信号，销毁animation
            connect(animat, &QPropertyAnimation::finished, this, [=]()
            {
                delete animat;
            });
        }
        return true;
    }
    return QObject::eventFilter(watched, event);
}

void RecBoxItem::setRecText(const QString &text)
{
    ui->recBoxItemText->setText(text);
}

void RecBoxItem::setRecImage(const QString &imageUrl)
{
    QString style =  "border-image:url("+imageUrl+");";
    ui->recMusicImage->setStyleSheet(style);
}
