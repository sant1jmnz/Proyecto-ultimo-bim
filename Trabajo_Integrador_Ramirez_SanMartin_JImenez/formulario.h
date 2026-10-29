#ifndef FORMULARIO_H
#define FORMULARIO_H

#include <QDialog>

namespace Ui {
class Formulario;
}

class Formulario : public QDialog
{
    Q_OBJECT

public:
    explicit Formulario(QWidget *parent = nullptr);
    ~Formulario();

    void cargarDatosEdicion(QString id, QString nombre, QString categoria,
                            double precio, int stock, bool aplicaIva, bool importado);

signals:
    void productoCreado(QString id, QString nombre, QString categoria,
                        double precio, int stock, bool aplicaIva, bool importado);
    void productoEditado(QString id, QString nombre, QString categoria,
                         double precio, int stock, bool aplicaIva, bool importado);

private slots:
    void on_btnGuardar_clicked();
    void on_btnCancelar_clicked();

private:
    Ui::Formulario *ui;
    bool modoEdicion = false;
};

#endif // FORMULARIO_H
