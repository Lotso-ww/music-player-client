#include "lrcpage.h"
#include "ui_lrcpage.h"

LrcPage::LrcPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LrcPage)
{
    ui->setupUi(this);

    // 设置窗口无标题栏
    setWindowFlag(Qt::FramelessWindowHint);

    // 关联hideBtn,点击进行隐藏
    connect(ui->hideBtn, &QPushButton::clicked, this, [=]{
       this->hide();
    });
}

LrcPage::~LrcPage()
{
    delete ui;
}
