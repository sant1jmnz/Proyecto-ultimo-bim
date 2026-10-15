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
    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    QSortFilterProxyModel *filtroInventario;
};
#endif // MAINWINDOW_H
