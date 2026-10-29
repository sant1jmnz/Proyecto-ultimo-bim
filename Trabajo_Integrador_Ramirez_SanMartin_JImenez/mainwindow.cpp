#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "formulario.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    modeloInventario = new QStandardItemModel(this);
    modeloInventario->setHorizontalHeaderLabels({"ID", "Nombre", "Categoría", "Precio", "Stock", "IVA", "Origen"});

    ui->tableView->setModel(modeloInventario);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnNuevo_clicked()
{
    Formulario *ventana = new Formulario(this);
    connect(ventana, &Formulario::productoCreado, this, &MainWindow::agregarProductoTabla);
    connect(ventana, &QDialog::finished, ventana, &QObject::deleteLater);
    ventana->show();
}

void MainWindow::agregarProductoTabla(QString id, QString nombre, QString categoria,
                                      double precio, int stock, bool aplicaIva, bool importado)
{
    QList<QStandardItem *> fila;
    fila << new QStandardItem(id.trimmed())
         << new QStandardItem(nombre.trimmed())
         << new QStandardItem(categoria)
         << new QStandardItem(QString::number(precio))
         << new QStandardItem(QString::number(stock))
         << new QStandardItem(aplicaIva ? "Sí" : "No")
         << new QStandardItem(importado ? "Importado" : "Nacional");
    modeloInventario->appendRow(fila);
}

void MainWindow::on_btnEditar_clicked()
{
    int fila = ui->tableView->currentIndex().row();
    if (fila == -1) {
        QMessageBox::warning(this, "Error", "No seleccionó ningún producto.");
        return;
    }
    filaEditando = fila;

    QString id = modeloInventario->item(fila, 0)->text();
    QString nombre = modeloInventario->item(fila, 1)->text();
    QString categoria = modeloInventario->item(fila, 2)->text();
    double precio = modeloInventario->item(fila, 3)->text().toDouble();
    int stock = modeloInventario->item(fila, 4)->text().toInt();
    bool aplicaIva = modeloInventario->item(fila, 5)->text() == "Sí";
    bool importado = modeloInventario->item(fila, 6)->text() == "Importado";

    Formulario *ventana = new Formulario(this);
    ventana->cargarDatosEdicion(id, nombre, categoria, precio, stock, aplicaIva, importado);
    connect(ventana, &Formulario::productoEditado, this, &MainWindow::actualizarProductoTabla);
    connect(ventana, &QDialog::finished, ventana, &QObject::deleteLater);
    ventana->show();
}

void MainWindow::actualizarProductoTabla(QString id, QString nombre, QString categoria,
                                         double precio, int stock, bool aplicaIva, bool importado)
{
    if (filaEditando < 0 || filaEditando >= modeloInventario->rowCount())
        return;

    modeloInventario->item(filaEditando, 0)->setText(id.trimmed());
    modeloInventario->item(filaEditando, 1)->setText(nombre.trimmed());
    modeloInventario->item(filaEditando, 2)->setText(categoria);
    modeloInventario->item(filaEditando, 3)->setText(QString::number(precio));
    modeloInventario->item(filaEditando, 4)->setText(QString::number(stock));
    modeloInventario->item(filaEditando, 5)->setText(aplicaIva ? "Sí" : "No");
    modeloInventario->item(filaEditando, 6)->setText(importado ? "Importado" : "Nacional");
    filaEditando = -1;
}
