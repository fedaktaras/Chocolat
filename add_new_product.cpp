#include "add_new_product.h"
#include "ui_add_new_product.h"
#include "add_new_type.h"

add_new_product::add_new_product(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_new_product)
{
    ui->setupUi(this);

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select type_name from type");
    query->exec();
    model->setQuery(*query);
    ui->comboBox->setModel(model);


}

add_new_product::~add_new_product()
{
    delete ui;
}

void add_new_product::on_pushButton_clicked()
{
    add_new_type *a = new add_new_type;
    a->show();
}

void add_new_product::on_pushButton_2_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select type_name from type");
    query->exec();
    model->setQuery(*query);
    ui->comboBox->setModel(model);
}

void add_new_product::on_buttonBox_accepted()
{
    QSqlQuery *query = new QSqlQuery;
    query->prepare("insert into in_stock (product_name, type_name, realisation_price, "
                   "is_recept, is_count, available_count, available_weight) "
                   "values (:a, :b, :c, :d, :e, :f, :g)");
    query->bindValue(":a", ui->lineEdit->text());
    query->bindValue(":b", ui->comboBox->currentText());
    query->bindValue(":c", ui->doubleSpinBox->value());
    query->bindValue(":d", ui->checkBox->isChecked());
    bool ch1 = ui->checkBox_2->isChecked();
    query->bindValue(":e", !ch1);
    if (!ch1)
    {
        query->bindValue(":f", 0);
    }
    else
    {
        query->bindValue(":g", "NULL");
    }
    query->exec();

}

void add_new_product::on_pushButton_3_clicked()
{
    QSqlQuery *query = new QSqlQuery;
    query->prepare("insert into in_stock (product_name, type_name, realisation_price, "
                   "is_recept, is_count, available_count, available_weight) "
                   "values (:a, :b, :c, :d, :e, :f, :g)");
    query->bindValue(":a", ui->lineEdit->text());
    query->bindValue(":b", ui->comboBox->currentText());
    query->bindValue(":c", ui->doubleSpinBox->value());
    query->bindValue(":d", ui->checkBox->isChecked());
    bool ch1 = ui->checkBox_2->isChecked();
    query->bindValue(":e", !ch1);
    if (!ch1)
    {
        query->bindValue(":f", 0);

    }
    else
    {
        query->bindValue(":g", 0);

    }
    query->exec();
    ui->lineEdit->clear();
    ui->doubleSpinBox->clear();
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
}
