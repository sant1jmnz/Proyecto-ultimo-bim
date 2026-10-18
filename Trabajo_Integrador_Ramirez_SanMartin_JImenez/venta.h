#ifndef VENTA_H
#define VENTA_H

#include <QDialog>

namespace Ui {
class Venta;
}

class Venta : public QDialog
{
    Q_OBJECT

public:
    void cargarDatos(QString nombreProducto, QString cantidadStock);
    explicit Venta(QWidget *parent = nullptr);
    ~Venta();

private slots:
    void on_btnCancelar_clicked();

    void on_btnConfirmar_clicked();

private:
    Ui::Venta *ui;
};

#endif
