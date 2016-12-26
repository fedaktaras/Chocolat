#include "new_sell.h"
#include "ui_new_sell.h"


new_sell::new_sell(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_sell)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(1, 140);
    ui->tableWidget->setColumnWidth(2, 140);
    ui->tableWidget->setColumnWidth(0, 230);

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select type_name from type where is_ingredient = 0 ");
    query->exec();
    model->setQuery(*query);
    ui->listView->setModel(model);
    if (ui->tableWidget->rowCount()<1)
    {
        ui->pushButton_2->setEnabled(false);
        ui->pushButton->setEnabled(false);
    }
    else
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton->setEnabled(true);
    }
    QShortcut *right = new QShortcut(QKeySequence(Qt::Key_Right), ui->listView);
    connect(right, SIGNAL(activated()), this, SLOT(switch_lists()));
    QShortcut *left = new QShortcut(QKeySequence(Qt::Key_Left), ui->listView_2);
    connect(left, SIGNAL(activated()), this, SLOT(switch_lists2()));
    QShortcut *deletelast = new QShortcut(QKeySequence(Qt::Key_Backspace), ui->tableWidget);
    connect(deletelast, SIGNAL(activated()), this, SLOT(delete_last()));
}

void new_sell::switch_lists()           //switch to right listview
{
    ui->listView_2->setFocus();
}

void new_sell::switch_lists2()           //switch to left listview)
{
    ui->listView->setFocus();
}

void new_sell::delete_last()            // delete last
{
    ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
    double total = 0;
    for (int i = 0; i<ui->tableWidget->rowCount(); i++)
    {
        total += (ui->tableWidget->item(i, 1)->QTableWidgetItem::data(Qt::DisplayRole).toDouble())*(ui->tableWidget->item(i, 2)->QTableWidgetItem::data(Qt::DisplayRole).toDouble());
    }
    QString Str_total = QString("%1").arg(total);
    ui->label_3->setText(Str_total);
}

new_sell::~new_sell()
{
    delete ui;
}



void new_sell::on_listView_activated(const QModelIndex &index)              //chose type
{

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select product_name from in_stock where type_name = :a");
    query->bindValue(":a", index.data().toString());
    query->exec();
    model->setQuery(*query);
    ui->listView_2->setModel(model);
}

void new_sell::on_listView_2_activated(const QModelIndex &index)                    // inserting in tableWidget
{
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select is_count from in_stock where product_name = :a");
    query->bindValue(":a", index.data().toString());
    query->exec();
    query->next();

    bool is_count = query->value(0).toBool();               //set amount by defoult
    double amount;
    if (is_count)
    {
        amount = 1;
    }
    else
    {
        amount = 0.100;
    }

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QSqlQuery *query1 = new QSqlQuery;

    query1->prepare("select realisation_price from in_stock where product_name = :a");
    query1->bindValue(":a", ui->listView_2->currentIndex().data().toString());
    query1->exec();
    query1->next();
    double price = query1->value(0).toDouble();
    QTableWidgetItem *item0 = new QTableWidgetItem(tr("%1").arg(ui->listView_2->currentIndex().data().toString()));
    QTableWidgetItem *item1 = new QTableWidgetItem(tr("%2").arg(price));
    QTableWidgetItem *item2 = new QTableWidgetItem(tr("%3").arg(amount));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, item0);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, item1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, item2);
    if (ui->tableWidget->rowCount()<1)
    {
        ui->pushButton_2->setEnabled(false);
        ui->pushButton->setEnabled(false);
    }
    else
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton->setEnabled(true);
    }

    double total = 0;
    for (int i = 0; i<ui->tableWidget->rowCount(); i++)
    {
        double price = ui->tableWidget->item(i, 1)->QTableWidgetItem::data(Qt::DisplayRole).toDouble();
        double amount = ui->tableWidget->item(i, 2)->QTableWidgetItem::data(Qt::DisplayRole).toDouble();
        total += amount*price;
    }
    QString Str_total = QString("%1").arg(total);
    ui->label_3->setText(Str_total);
}

void new_sell::on_pushButton_2_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());


    if (ui->tableWidget->rowCount()<1)
    {
        ui->pushButton_2->setEnabled(false);
        ui->pushButton->setEnabled(false);
    }
    else
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton->setEnabled(true);
    }

    double total = 0;
    for (int i = 0; i<ui->tableWidget->rowCount(); i++)
    {
        double price = ui->tableWidget->item(i, 1)->QTableWidgetItem::data(Qt::DisplayRole).toDouble();
        double amount = ui->tableWidget->item(i, 2)->QTableWidgetItem::data(Qt::DisplayRole).toDouble();
        total += amount*price;
    }
    QString Str_total = QString("%1").arg(total);
    ui->label_3->setText(Str_total);

}

void new_sell::on_tableWidget_itemSelectionChanged()
{
    double total = 0;
    for (int i = 0; i<ui->tableWidget->rowCount(); i++)
    {
        total += (ui->tableWidget->item(i, 1)->QTableWidgetItem::data(Qt::DisplayRole).toDouble())*(ui->tableWidget->item(i, 2)->QTableWidgetItem::data(Qt::DisplayRole).toDouble());
    }
    QString Str_total = QString("%1").arg(total);
    ui->label_3->setText(Str_total);
}



void new_sell::on_pushButton_clicked()  //підтвердити
{
    QMessageBox a;
    a.setText("Готово");
    a.setWindowTitle("Done");
    a.show();

    QSqlQuery *query = new QSqlQuery;
    QSqlQuery *query1 = new QSqlQuery;
    QSqlQuery *query2 = new QSqlQuery;

    for (int i =0; i < ui->tableWidget->rowCount(); ++i)
    {
        query->prepare("select is_count from in_stock where product_name = :a");
        query->bindValue(":a", ui->tableWidget->item(i, 1)->data(Qt::DisplayRole).toString());
        query->exec();
        query->next();

        bool is_count = query->value(0).toBool();

        if (is_count)
        {
            int int_amount = ui->tableWidget->item(i, 2)->data(Qt::DisplayRole).toInt();
            query2->prepare("update in_stock set available_count=available_count-:b where product_name = :c" );
            query2->bindValue(":b", int_amount);

            query1->prepare("insert into sails_records (name, amount_int, total_price) values (:a, :b, :c)");
            query1->bindValue(":b", int_amount);
        }
        else
        {
            double double_amount = ui->tableWidget->item(i, 2)->data(Qt::DisplayRole).toInt();
            query2->prepare("update in_stock set available_count=available_count-:b where product_name = :c" );
            query2->bindValue(":b", double_amount);

            query1->prepare("insert into sails_records (name, amount_int, total_price) values (:a, :b, :c)");
            query1->bindValue(":b", double_amount);
        }
        query1->bindValue(":a", ui->tableWidget->item(i, 0)->data(Qt::DisplayRole).toString());
        query1->bindValue(":c", (ui->tableWidget->item(i, 2)->data(Qt::DisplayRole).toDouble()*ui->tableWidget->item(i, 1)->data(Qt::DisplayRole).toDouble()));
        query1->exec();
        query2->bindValue(":c", ui->tableWidget->item(i, 0)->data(Qt::DisplayRole).toString());
        query2->exec();
    }
    this->close();
}
