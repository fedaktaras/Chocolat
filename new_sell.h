#ifndef NEW_SELL_H
#define NEW_SELL_H

#include <QDialog>

namespace Ui {
class new_sell;
}

class new_sell : public QDialog
{
    Q_OBJECT

public:
    explicit new_sell(QWidget *parent = 0);
    ~new_sell();

private:
    Ui::new_sell *ui;
};

#endif // NEW_SELL_H
