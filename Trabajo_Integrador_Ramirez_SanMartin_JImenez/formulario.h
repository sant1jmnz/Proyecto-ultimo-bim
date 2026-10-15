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

private:
    Ui::Formulario *ui;
};

#endif // FORMULARIO_H
