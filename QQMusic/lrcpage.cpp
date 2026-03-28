#include "lrcpage.h"
#include "ui_lrcpage.h"

LrcPage::LrcPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LrcPage)
{
    ui->setupUi(this);
}

LrcPage::~LrcPage()
{
    delete ui;
}
