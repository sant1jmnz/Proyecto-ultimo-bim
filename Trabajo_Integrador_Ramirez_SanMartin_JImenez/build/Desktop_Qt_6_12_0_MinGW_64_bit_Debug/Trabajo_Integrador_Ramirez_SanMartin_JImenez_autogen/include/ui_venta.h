/********************************************************************************
** Form generated from reading UI file 'venta.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENTA_H
#define UI_VENTA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Venta
{
public:
    QLabel *lblImagen;
    QLabel *label_2;
    QSpinBox *spinCantidad;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *btnConfirmar;
    QPushButton *btnCancelar;
    QLabel *lblProducto;
    QLabel *lblStock;

    void setupUi(QDialog *Venta)
    {
        if (Venta->objectName().isEmpty())
            Venta->setObjectName("Venta");
        Venta->resize(400, 300);
        lblImagen = new QLabel(Venta);
        lblImagen->setObjectName("lblImagen");
        lblImagen->setGeometry(QRect(30, 80, 171, 101));
        label_2 = new QLabel(Venta);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(220, 120, 49, 16));
        spinCantidad = new QSpinBox(Venta);
        spinCantidad->setObjectName("spinCantidad");
        spinCantidad->setGeometry(QRect(300, 110, 80, 30));
        spinCantidad->setStyleSheet(QString::fromUtf8("color: black; background-color: white;"));
        spinCantidad->setValue(1);
        label_3 = new QLabel(Venta);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 20, 51, 16));
        label_4 = new QLabel(Venta);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 50, 91, 16));
        btnConfirmar = new QPushButton(Venta);
        btnConfirmar->setObjectName("btnConfirmar");
        btnConfirmar->setGeometry(QRect(190, 260, 101, 24));
        btnCancelar = new QPushButton(Venta);
        btnCancelar->setObjectName("btnCancelar");
        btnCancelar->setGeometry(QRect(310, 260, 80, 24));
        lblProducto = new QLabel(Venta);
        lblProducto->setObjectName("lblProducto");
        lblProducto->setGeometry(QRect(140, 20, 49, 16));
        lblStock = new QLabel(Venta);
        lblStock->setObjectName("lblStock");
        lblStock->setGeometry(QRect(180, 50, 49, 16));

        retranslateUi(Venta);

        QMetaObject::connectSlotsByName(Venta);
    } // setupUi

    void retranslateUi(QDialog *Venta)
    {
        Venta->setWindowTitle(QCoreApplication::translate("Venta", "Dialog", nullptr));
        lblImagen->setText(QCoreApplication::translate("Venta", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("Venta", "Cantidad:", nullptr));
        label_3->setText(QCoreApplication::translate("Venta", "Producto:", nullptr));
        label_4->setText(QCoreApplication::translate("Venta", "Stock disponible:", nullptr));
        btnConfirmar->setText(QCoreApplication::translate("Venta", "Confirmar Venta", nullptr));
        btnCancelar->setText(QCoreApplication::translate("Venta", "Cancelar", nullptr));
        lblProducto->setText(QCoreApplication::translate("Venta", "TextLabel", nullptr));
        lblStock->setText(QCoreApplication::translate("Venta", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Venta: public Ui_Venta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENTA_H
