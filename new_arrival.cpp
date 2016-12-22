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

void new_arrival::on_comboBox_2_currentIndexChanged()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select product_name from in_stock where type_name = :a");
    query->bindValue(":a", ui->comboBox_2->currentText());
    query->exec();
    model->setQuery(*query);
    ui->comboBox->setModel(model);
}


void new_arrival::on_pushButtonadd_clicked()
{
    //QSqlQueryModel *model1 = new QSqlQueryModel;
    QSqlQuery *query1 = new QSqlQuery;
    //QSqlQueryModel *model2 = new QSqlQueryModel;
    QSqlQuery *query2 = new QSqlQuery;
    query1->prepare("select is_count from in_stock where product_name = :a");
    query1->bindValue(":a", ui->comboBox->currentText());
    query1->exec();
    QSqlRecord qr = query1->record();
    query1->next();


    bool is_count = query1->value(0).toBool();//qr.value("is_count").toBool();

    if (is_count)
    {
        query2->prepare("update in_stock set available_count=:b+available_count where product_name = :c" );
        query2->bindValue(":b", ui->lineEdit->text().toInt());
    }
    else
    {
        query2->prepare("update in_stock set available_weight = :b+available_weight where product_name = :c" );
        query2->bindValue(":b", ui->lineEdit->text().toDouble());
    }
    query2->bindValue(":c", ui->comboBox->currentText());
    query2->exec();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}
