/********************************************************************************
** Form generated from reading UI file 'formulario.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMULARIO_H
#define UI_FORMULARIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_Formulario
{
public:
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QCheckBox *checkBox;
    QComboBox *comboBox;

    void setupUi(QDialog *Formulario)
    {
        if (Formulario->objectName().isEmpty())
            Formulario->setObjectName("Formulario");
        Formulario->resize(622, 443);
        Formulario->setStyleSheet(QString::fromUtf8("background: black;\n"
""));
        groupBox = new QGroupBox(Formulario);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(40, 90, 331, 271));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(20, 150, 110, 23));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(20, 180, 110, 23));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(20, 230, 91, 23));
        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(20, 40, 86, 26));

        retranslateUi(Formulario);

        QMetaObject::connectSlotsByName(Formulario);
    } // setupUi

    void retranslateUi(QDialog *Formulario)
    {
        Formulario->setWindowTitle(QCoreApplication::translate("Formulario", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Formulario", "GroupBox", nullptr));
        radioButton->setText(QCoreApplication::translate("Formulario", "Nacional", nullptr));
        radioButton_2->setText(QCoreApplication::translate("Formulario", "Importado", nullptr));
        checkBox->setText(QCoreApplication::translate("Formulario", "Aplica IVA", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Formulario", "Alimentos", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Formulario", "Limpieza", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Formulario", "Bazar", nullptr));

    } // retranslateUi

};

namespace Ui {
    class Formulario: public Ui_Formulario {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMULARIO_H
