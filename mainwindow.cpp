#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QStandardPaths>
#include <QShortcut>
#include "new_sell.h"
#include "add_new_product.h"
#include "new_arrival.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase choc_db = QSqlDatabase::addDatabase("QSQLITE");
    choc_db.setDatabaseName("D:/Chocolate.sqlite");

    if(!choc_db.open())
    {
        ui->statusBar->showMessage("З'єднання не встановленно", 100000);
    }
    else
    {
        ui->statusBar->showMessage("Встановленно з'єднання", 100000);
    }
    QShortcut *sell = new QShortcut(QKeySequence(Qt::Key_Home), ui->pushButton);
    connect(sell, SIGNAL(activated()), this, SLOT(on_pushButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    new_sell *a = new new_sell;
    a->show();
}

void MainWindow::on_action_triggered()
{
    add_new_product *a = new add_new_product;
    a->show();
}

void MainWindow::on_action_3_triggered()
{
    new_arrival *a = new new_arrival;
    a->show();
}
