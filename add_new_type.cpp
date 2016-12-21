#include "add_new_type.h"
#include "ui_add_new_type.h"

add_new_type::add_new_type(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_new_type)
{
    ui->setupUi(this);

}

add_new_type::~add_new_type()
{
    delete ui;
}

void add_new_type::on_buttonBox_accepted()
{
    QSqlQuery *query = new QSqlQuery;
    QString type_name = ui->lineEdit->text();
    bool is_count = ui->checkBox->isChecked();
    bool is_ingredient = ui->checkBox_2->isChecked();
    query->prepare("insert into type (type_name, is_count, is_ingredient) values (:a, :b, :c)");
    query->bindValue(":a", type_name);
    query->bindValue(":b", !is_count);
    query->bindValue(":c", is_ingredient);
    query->exec();
}
