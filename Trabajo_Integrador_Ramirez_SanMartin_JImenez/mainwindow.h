#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QCloseEvent>

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

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void on_tableView_clicked(const QModelIndex &index);
    void on_btnNuevo_clicked();
    void agregarProductoTabla(QString id, QString nombre, QString categoria,
                              double precio, int stock, bool aplicaIva, bool importado);
    void actualizarProductoTabla(QString id, QString nombre, QString categoria,
                                 double precio, int stock, bool aplicaIva, bool importado);
    void on_btnRegistrar_clicked();
    void on_btnEditar_clicked();
    void on_btnEliminar_clicked();
    void mostrarMenuContextual(QPoint posicion);
    void guardarDatos();
    void cargarDatos();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *modeloInventario;
    QSortFilterProxyModel *filtroInventario;
    int filaEditando = -1; // fila del modelo que se esta editando
};
#endif // MAINWINDOW_H
