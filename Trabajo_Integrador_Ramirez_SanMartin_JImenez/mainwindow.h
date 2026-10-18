#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>

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
    void on_actionRegistrar_venta_triggered();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_tableView_activated(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    QSortFilterProxyModel *filtroInventario;
};
#endif // MAINWINDOW_H
