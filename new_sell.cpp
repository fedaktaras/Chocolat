#include "new_sell.h"
#include "ui_new_sell.h"

new_sell::new_sell(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_sell)
{
    ui->setupUi(this);
}

new_sell::~new_sell()
{
    delete ui;
}
