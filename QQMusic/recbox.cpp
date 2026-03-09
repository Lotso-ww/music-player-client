#include "recbox.h"
#include "ui_recbox.h"

#include "recboxitem.h"

RecBox::RecBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecBox)
{
    ui->setupUi(this);
    RecBoxItem* item = new RecBoxItem();
    ui->recListUpLayout->addWidget(item);
}

RecBox::~RecBox()
{
    delete ui;
}
