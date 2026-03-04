#include "btform.h"
#include "ui_btform.h"

btForm::btForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::btForm)
{
    ui->setupUi(this);
}

btForm::~btForm()
{
    delete ui;
}

void btForm::setIconAndText(const QString &btIconUrl, const QString &btText)
{
    // 设置图标
    ui->btIcon->setPixmap(QPixmap(btIconUrl));

    // 设置文本
    ui->btText->setText(btText);
}
