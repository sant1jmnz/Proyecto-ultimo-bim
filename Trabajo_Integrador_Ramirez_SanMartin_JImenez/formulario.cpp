#include "formulario.h"
#include "ui_formulario.h"
#include <QMessageBox>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QLocale>

Formulario::Formulario(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Formulario)
{
    ui->setupUi(this);

    auto *validadorPrecio = new QDoubleValidator(0, 999999, 2, this);
    validadorPrecio->setNotation(QDoubleValidator::StandardNotation);
    validadorPrecio->setLocale(QLocale::c());
    ui->lePrecio->setValidator(validadorPrecio);
    ui->leStock->setValidator(new QIntValidator(0, 9999, this));
}

Formulario::~Formulario()
{
    delete ui;
}

void Formulario::cargarDatosEdicion(QString id, QString nombre, QString categoria,
                                    double precio, int stock, bool aplicaIva, bool importado)
{
    modoEdicion = true;
    setWindowTitle("Editar producto");

    ui->leId->setText(id);
    ui->leNombre->setText(nombre);
    ui->cbCategoria->setCurrentText(categoria);
    ui->lePrecio->setText(QString::number(precio));
    ui->leStock->setText(QString::number(stock));
    ui->chkIva->setChecked(aplicaIva);
    ui->rbImportado->setChecked(importado);
    ui->rbNacional->setChecked(!importado);
}

void Formulario::on_btnGuardar_clicked()
{
    QString id = ui->leId->text();
    QString nombre = ui->leNombre->text();
    QString textoPrecio = ui->lePrecio->text();
    QString textoStock = ui->leStock->text();

    if (id.isEmpty() || nombre.isEmpty() || textoPrecio.isEmpty() || textoStock.isEmpty()) {
        QMessageBox::warning(this, "Error", "Debe completar todos los campos.");
        return;
    }

    double precio = textoPrecio.toDouble();
    int stock = textoStock.toInt();
    QString categoria = ui->cbCategoria->currentText();
    bool aplicaIva = ui->chkIva->isChecked();
    bool importado = ui->rbImportado->isChecked();

    if (modoEdicion) {
        emit productoEditado(id, nombre, categoria, precio, stock, aplicaIva, importado);
    } else {
        emit productoCreado(id, nombre, categoria, precio, stock, aplicaIva, importado);
    }
    this->close();
}

void Formulario::on_btnCancelar_clicked()
{
    this->close();
}
