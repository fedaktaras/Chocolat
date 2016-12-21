#include "new_arrival.h"
#include "ui_new_arrival.h"

new_arrival::new_arrival(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_arrival)
{
    ui->setupUi(this);
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select type_name from type");
    query->exec();
    model->setQuery(*query);
    ui->comboBox_2->setModel(model);
}

new_arrival::~new_arrival()
{
    delete ui;
}
