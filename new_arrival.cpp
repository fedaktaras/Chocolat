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
    QSqlQuery *query = new QSqlQuery;
    QSqlQuery *query1 = new QSqlQuery;
    QSqlQuery *query2 = new QSqlQuery;

    query->prepare("select is_count from in_stock where product_name = :a");
    query->bindValue(":a", ui->comboBox->currentText());
    query->exec();
    query->next();

    bool is_count = query->value(0).toBool();

    if (is_count)
    {
        query2->prepare("update in_stock set available_count=:b+available_count where product_name = :c" );
        query2->bindValue(":b", ui->lineEditAmount->text().toInt());

        query1->prepare("insert into arrivals (product_name, amount, total_price, price_per_one_or_kg,"
                        "company_name) values (:a, :b, :c, :d, :e)");
        query1->bindValue(":b", ui->lineEditAmount->text().toInt());
    }
    else
    {
        query2->prepare("update in_stock set available_weight = :b+available_weight where product_name = :c" );
        query2->bindValue(":b", ui->lineEditAmount->text().toDouble());

        query1->prepare("insert into arrivals (product_name, amount_kg, total_price, price_per_one_or_kg,"
                        "company_name) values (:a, :b, :c, :d, :e)");
        query1->bindValue(":b", ui->lineEditAmount->text().toDouble());
    }
    query2->bindValue(":c", ui->comboBox->currentText());
    query2->exec();


    query1->bindValue(":a", ui->comboBox->currentText());
    query1->bindValue(":c", ui->lineEditPrice->text().toDouble());

    double x = (ui->lineEditPrice->text().toDouble())/(ui->lineEditAmount->text().toDouble());
    x *= 100;
    x = std::floor(x);
    x /= 100;
    query1->bindValue(":d", x);
    query1->bindValue(":e", ui->lineEditCompany->text());


    query1->exec();

    ui->lineEditAmount->clear();
    ui->lineEditCompany->clear();
    ui->lineEditPrice->clear();

}
