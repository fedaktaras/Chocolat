#ifndef ADD_NEW_PRODUCT_H
#define ADD_NEW_PRODUCT_H

#include <QDialog>
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>


namespace Ui {
class add_new_product;
}

class add_new_product : public QDialog
{
    Q_OBJECT

public:
    explicit add_new_product(QWidget *parent = 0);
    ~add_new_product();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::add_new_product *ui;

};

#endif // ADD_NEW_PRODUCT_H
