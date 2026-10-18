#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "venta.h"
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStandardItemModel *modeloPrueba = new QStandardItemModel(this);
    modeloPrueba->setHorizontalHeaderLabels({"Producto", "Stock", "Precio"});

    QList<QStandardItem *> fila1 = {new QStandardItem("awdaw"), new QStandardItem("15"), new QStandardItem("45000")};
    QList<QStandardItem *> fila2 = {new QStandardItem("awdawdsaw"), new QStandardItem("8"), new QStandardItem("25000")};

    modeloPrueba->appendRow(fila1);
    modeloPrueba->appendRow(fila2);

    ui->tableView->setModel(modeloPrueba);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

}


void MainWindow::on_actionRegistrar_venta_triggered()
{
    Venta ventanaVenta(this);

    ventanaVenta.exec();
}


void MainWindow::on_tableView_activated(const QModelIndex &index)
{

}


void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    int fila = index.row();

    QString nombre = ui->tableView->model()->index(fila, 0).data().toString();
    QString stock = ui->tableView->model()->index(fila, 1).data().toString();

    Venta ventanaVenta(this);
    ventanaVenta.cargarDatos(nombre, stock);
    ventanaVenta.exec();
}
