#include "formulario.h"
#include "ui_formulario.h"

Formulario::Formulario(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Formulario)
{
    ui->setupUi(this);
}

Formulario::~Formulario()
{
    delete ui;
}
