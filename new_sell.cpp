#include "new_sell.h"
#include "ui_new_sell.h"


new_sell::new_sell(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_sell)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select type_name from type where is_ingredient = 0 ");
    query->exec();
    model->setQuery(*query);
    ui->listView->setModel(model);
    if (ui->tableWidget->rowCount()<1)
        ui->pushButton_2->setEnabled(false);
    else
        ui->pushButton_2->setEnabled(true);

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

void new_sell::on_listView_2_activated()
{
    //QSqlQueryModel *model = new QSqlQueryModel;
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QSqlQuery *query1 = new QSqlQuery;
    //QSqlQuery *query2 = new QSqlQuery;
    //QSqlQuery *query3 = new QSqlQuery;
    query1->prepare("select realisation_price from in_stock where product_name = :a");
    query1->bindValue(":a", ui->listView_2->currentIndex().data().toString());
    query1->exec();
    query1->next();
    double price = query1->value(0).toDouble();
    QTableWidgetItem *item0 = new QTableWidgetItem(tr("%1").arg(ui->listView_2->currentIndex().data().toString()));
    QTableWidgetItem *item1 = new QTableWidgetItem(tr("%2").arg(price));
    //QTableWidgetItem *item2 = new QTableWidgetItem(tr("%1").arg(ui->listView_2->currentIndex().data().toString()));
    ui->tableWidget->setItem(tableRow, 0, item0);
    ui->tableWidget->setItem(tableRow, 1, item1);
    tableRow++;
    if (ui->tableWidget->rowCount()<1)
        ui->pushButton_2->setEnabled(false);
    else
        ui->pushButton_2->setEnabled(true);
    //double total = 0;
    double total = 0;
    for (int i = 0; i<ui->tableWidget->rowCount(); i++)
    {
        total += ui->tableWidget->item(i, 1)->QTableWidgetItem::data(Qt::DisplayRole).toDouble();
    }
    QString Str_total = QString("%1").arg(total);
    ui->label_3->setText(Str_total);
}

void new_sell::on_pushButton_2_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
    tableRow--;
    if (ui->tableWidget->rowCount()<1)
        ui->pushButton_2->setEnabled(false);
    else
        ui->pushButton_2->setEnabled(true);
    //double total = 0;
    double total = 0;
    for (int i = 0; i<ui->tableWidget->rowCount(); i++)
    {
        total += ui->tableWidget->item(i, 1)->QTableWidgetItem::data(Qt::DisplayRole).toDouble();
    }
    QString Str_total = QString("%1").arg(total);
    ui->label_3->setText(Str_total);

}

void new_sell::on_tableWidget_itemSelectionChanged()
{
    double total = 0;
    for (int i = 0; i<ui->tableWidget->rowCount(); i++)
    {
        total += ui->tableWidget->item(i, 1)->QTableWidgetItem::data(Qt::DisplayRole).toDouble();
    }
    QString Str_total = QString("%1").arg(total);
    ui->label_3->setText(Str_total);
}

