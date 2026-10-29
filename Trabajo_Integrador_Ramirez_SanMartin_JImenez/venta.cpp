#include "venta.h"
#include "ui_venta.h"
#include <QMessageBox>
#include <QPixmap>

Venta::Venta(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Venta)
{
    ui->setupUi(this);
}

Venta::~Venta()
{
    delete ui;
}

void Venta::on_btnCancelar_clicked()
{
    close();
}


void Venta::on_btnConfirmar_clicked()
{
    int cantidad = ui->spinCantidad->value();

    int stock = ui->lblStock->text().toInt();

    if (cantidad <= 0) {
        QMessageBox::warning(this, "Error", "La cantidad a vender debe ser al menos 1.");
        return;
    }

    if (cantidad > stock) {
        QMessageBox::warning(this, "Alerta de Stock", "No hay suficiente stock para vender esa cantidad.");
        return;
    }

    accept();
}
void Venta::cargarDatos(QString nombreProducto, QString cantidadStock)
{
    ui->lblProducto->setText(nombreProducto);
    ui->lblStock->setText(cantidadStock);
    ui->spinCantidad->setRange(1, 999999);

    QPixmap foto(":/imagenes/imagenes/" + nombreProducto + ".jpg");
    if (foto.isNull()) {
        foto.load(":/imagenes/imagenes/default.png");
    }
    foto = foto.scaled(ui->lblImagen->size(), Qt::KeepAspectRatio);
    ui->lblImagen->setPixmap(foto);
}

int Venta::cantidad()
{
    return ui->spinCantidad->value();
}
