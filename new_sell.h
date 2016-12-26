#ifndef NEW_SELL_H
#define NEW_SELL_H

#include <QDialog>
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>
#include <QTableWidgetItem>
#include <QShortcut>
#include <QMessageBox>
#include "ui_new_sell.h"

namespace Ui {
class new_sell;
}

class new_sell : public QDialog
{
    Q_OBJECT

public:
    explicit new_sell(QWidget *parent = 0);
    ~new_sell();

private slots:


    void on_listView_activated(const QModelIndex &index);

    void on_listView_2_activated(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_tableWidget_itemSelectionChanged();


    void on_pushButton_clicked();
    void switch_lists();
    void switch_lists2();
    void delete_last();

private:

    Ui::new_sell *ui;
};

#endif // NEW_SELL_H
