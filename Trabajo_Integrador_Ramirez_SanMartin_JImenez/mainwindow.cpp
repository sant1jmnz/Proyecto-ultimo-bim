#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "venta.h"
#include "formulario.h"
#include <QMenu>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    modeloInventario = new QStandardItemModel(this);
    modeloInventario->setHorizontalHeaderLabels({"ID", "Nombre", "Categoría", "Precio", "Stock", "IVA", "Origen"});

    filtroInventario = new QSortFilterProxyModel(this);
    filtroInventario->setFilterKeyColumn(-1);
    filtroInventario->setSourceModel(modeloInventario);

    ui->tableView->setModel(filtroInventario);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->btnRegistrar->setEnabled(false);
    ui->btnEditar->setEnabled(false);
    ui->btnEliminar->setEnabled(false);

    connect(ui->tableView, &QTableView::customContextMenuRequested, this, &MainWindow::mostrarMenuContextual);
    connect(ui->tableView, &QTableView::doubleClicked, this, &MainWindow::on_btnRegistrar_clicked);
    connect(ui->actionRegistrar_venta, &QAction::triggered, this, &MainWindow::on_btnRegistrar_clicked);
    connect(ui->actionEditar, &QAction::triggered, this, &MainWindow::on_btnEditar_clicked);
    connect(ui->actionEliminar, &QAction::triggered, this, &MainWindow::on_btnEliminar_clicked);

    cargarDatos();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    filtroInventario->setFilterFixedString(arg1);

    if (filtroInventario->rowCount() == 0) {
        ui->btnRegistrar->setEnabled(false);
        ui->btnEditar->setEnabled(false);
        ui->btnEliminar->setEnabled(false);
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        ui->btnRegistrar->setEnabled(true);
        ui->btnEditar->setEnabled(true);
        ui->btnEliminar->setEnabled(true);
    }
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

void MainWindow::on_btnRegistrar_clicked()
{
    int fila = ui->tableView->currentIndex().row();
    if (fila == -1) {
        QMessageBox::warning(this, "Error", "No seleccionó ningún producto.");
        return;
    }
    fila = filtroInventario->mapToSource(ui->tableView->currentIndex()).row();

    Venta ventanaVenta(this);
    ventanaVenta.cargarDatos(modeloInventario->item(fila, 1)->text(), modeloInventario->item(fila, 4)->text());

    if (ventanaVenta.exec() == QDialog::Accepted) {
        int stockActual = modeloInventario->item(fila, 4)->text().toInt();
        int nuevoStock = stockActual - ventanaVenta.cantidad();
        modeloInventario->item(fila, 4)->setText(QString::number(nuevoStock));

        if (nuevoStock == 0) {
            QMessageBox::information(this, "Sin stock", "El producto se quedó sin stock.");
        }
    }
}

void MainWindow::on_btnEditar_clicked()
{
    int fila = ui->tableView->currentIndex().row();
    if (fila == -1) {
        QMessageBox::warning(this, "Error", "No seleccionó ningún producto.");
        return;
    }
    fila = filtroInventario->mapToSource(ui->tableView->currentIndex()).row();
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

void MainWindow::on_btnEliminar_clicked()
{
    int fila = ui->tableView->currentIndex().row();
    if (fila == -1) {
        QMessageBox::warning(this, "Error", "No seleccionó ningún producto.");
        return;
    }
    fila = filtroInventario->mapToSource(ui->tableView->currentIndex()).row();

    modeloInventario->removeRow(fila);

    ui->btnRegistrar->setEnabled(false);
    ui->btnEditar->setEnabled(false);
    ui->btnEliminar->setEnabled(false);
}

void MainWindow::mostrarMenuContextual(QPoint posicion)
{
    QModelIndex indice = ui->tableView->indexAt(posicion);
    if (!indice.isValid())
        return;
    ui->tableView->setCurrentIndex(indice);
    on_tableView_clicked(indice);

    QMenu *menu = new QMenu(this);
    QAction *accionVenta = menu->addAction("Registrar venta");
    QAction *accionEditar = menu->addAction("Editar");
    QAction *accionEliminar = menu->addAction("Eliminar");

    QAction *accionSeleccionada = menu->exec(ui->tableView->viewport()->mapToGlobal(posicion));
    if (accionSeleccionada == accionVenta) {
        on_btnRegistrar_clicked();
    } else if (accionSeleccionada == accionEditar) {
        on_btnEditar_clicked();
    } else if (accionSeleccionada == accionEliminar) {
        on_btnEliminar_clicked();
    }
    menu->deleteLater();
}

void MainWindow::guardarDatos()
{
    QFile archivo("datos.bin");

    if (archivo.open(QIODevice::WriteOnly)) {
        QDataStream salida(&archivo);

        int cantidadFilas = modeloInventario->rowCount();
        salida << cantidadFilas;

        for (int fila = 0; fila < cantidadFilas; ++fila) {
            QString id = modeloInventario->item(fila, 0)->text();
            QString nombre = modeloInventario->item(fila, 1)->text();
            QString categoria = modeloInventario->item(fila, 2)->text();
            double precio = modeloInventario->item(fila, 3)->text().toDouble();
            int stock = modeloInventario->item(fila, 4)->text().toInt();
            bool aplicaIva = modeloInventario->item(fila, 5)->text() == "Sí";
            bool importado = modeloInventario->item(fila, 6)->text() == "Importado";

            salida << id << nombre << categoria << precio << stock << aplicaIva << importado;
        }

        archivo.close();
    }
}

void MainWindow::cargarDatos()
{
    QFile archivo("datos.bin");

    if (archivo.open(QIODevice::ReadOnly)) {
        QDataStream entrada(&archivo);

        int cantidadFilas = 0;
        entrada >> cantidadFilas;

        for (int fila = 0; fila < cantidadFilas; ++fila) {
            QString id, nombre, categoria;
            double precio;
            int stock;
            bool aplicaIva, importado;

            entrada >> id >> nombre >> categoria >> precio >> stock >> aplicaIva >> importado;

            if (entrada.status() != QDataStream::Ok)
                break;

            QList<QStandardItem *> filaNueva;
            filaNueva << new QStandardItem(id)
                      << new QStandardItem(nombre)
                      << new QStandardItem(categoria)
                      << new QStandardItem(QString::number(precio))
                      << new QStandardItem(QString::number(stock))
                      << new QStandardItem(aplicaIva ? "Sí" : "No")
                      << new QStandardItem(importado ? "Importado" : "Nacional");

            modeloInventario->appendRow(filaNueva);
        }

        archivo.close();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    guardarDatos();
    event->accept();
}
