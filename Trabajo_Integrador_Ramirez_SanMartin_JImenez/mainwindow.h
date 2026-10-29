#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btnNuevo_clicked();
    void on_btnEditar_clicked();
    void on_btnRegistrar_clicked();
    void agregarProductoTabla(QString id, QString nombre, QString categoria,
                              double precio, int stock, bool aplicaIva, bool importado);
    void actualizarProductoTabla(QString id, QString nombre, QString categoria,
                                 double precio, int stock, bool aplicaIva, bool importado);

private:
    // Columnas del modelo: ID, Nombre, Categoria, Precio, Stock, IVA, Origen
    Ui::MainWindow *ui;
    QStandardItemModel *modeloInventario;
    int filaEditando = -1; // fila del modelo que se esta editando
};
#endif // MAINWINDOW_H
