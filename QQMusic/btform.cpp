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
