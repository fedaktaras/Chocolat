#include "new_sell.h"
#include "ui_new_sell.h"

new_sell::new_sell(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_sell)
{

    ui->setupUi(this);
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select type_name from type where is_ingredient = 0 ");
    query->exec();
    model->setQuery(*query);
    ui->listView->setModel(model);
}

new_sell::~new_sell()
{
    delete ui;
}



void new_sell::on_listView_activated(const QModelIndex &index)
{

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select product_name from in_stock where type_name = :a");
    query->bindValue(":a", index.data().toString());
    query->exec();
    model->setQuery(*query);
    ui->listView_2->setModel(model);
}

void new_sell::on_listView_2_activated(const QModelIndex &index)
{
    //QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select realistion_prise from in_stock where product_name = :a");
    query->bindValue(":a", index.data().toString());
    query->exec();
    query->next();
    double price = query->value(0).toDouble();
    ui->tableWidget->setColumnCount(3);

}
