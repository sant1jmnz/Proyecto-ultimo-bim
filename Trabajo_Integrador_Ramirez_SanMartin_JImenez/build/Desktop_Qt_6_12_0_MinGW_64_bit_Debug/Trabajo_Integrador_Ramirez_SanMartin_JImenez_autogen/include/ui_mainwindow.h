/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRegistrar_venta;
    QAction *actionEditar;
    QAction *actionEliminar;
    QWidget *centralwidget;
    QTableView *tableView;
    QLineEdit *lineEdit;
    QMenuBar *menubar;
    QMenu *menuMENU;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: grey;"));
        actionRegistrar_venta = new QAction(MainWindow);
        actionRegistrar_venta->setObjectName("actionRegistrar_venta");
        actionEditar = new QAction(MainWindow);
        actionEditar->setObjectName("actionEditar");
        actionEliminar = new QAction(MainWindow);
        actionEliminar->setObjectName("actionEliminar");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(30, 100, 741, 391));
        tableView->setStyleSheet(QString::fromUtf8("background-color: black;"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(20, 40, 741, 26));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: black;"));
        lineEdit->setDragEnabled(false);
        lineEdit->setReadOnly(false);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuMENU = new QMenu(menubar);
        menuMENU->setObjectName("menuMENU");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMENU->menuAction());
        menuMENU->addAction(actionRegistrar_venta);
        menuMENU->addAction(actionEditar);
        menuMENU->addAction(actionEliminar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionRegistrar_venta->setText(QCoreApplication::translate("MainWindow", "Registrar venta", nullptr));
        actionEditar->setText(QCoreApplication::translate("MainWindow", "Editar", nullptr));
        actionEliminar->setText(QCoreApplication::translate("MainWindow", "Eliminar", nullptr));
        lineEdit->setPlaceholderText(QString());
        menuMENU->setTitle(QCoreApplication::translate("MainWindow", "MENU", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
