#ifndef NEW_ARRIVAL_H
#define NEW_ARRIVAL_H

#include <QDialog>
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>
#include <QSqlRecord>

namespace Ui {
class new_arrival;
}
//~new_arrival();
class new_arrival : public QDialog
{
    Q_OBJECT

public:
    explicit new_arrival(QWidget *parent = 0);
    ~new_arrival();

private slots:
    void on_comboBox_2_currentIndexChanged();

    void on_pushButtonadd_clicked();

private:
    Ui::new_arrival *ui;
};

#endif // NEW_ARRIVAL_H
