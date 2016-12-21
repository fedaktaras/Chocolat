#ifndef ADD_NEW_TYPE_H
#define ADD_NEW_TYPE_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class add_new_type;
}

class add_new_type : public QDialog
{
    Q_OBJECT

public:
    explicit add_new_type(QWidget *parent = 0);
    ~add_new_type();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::add_new_type *ui;
};

#endif // ADD_NEW_TYPE_H
