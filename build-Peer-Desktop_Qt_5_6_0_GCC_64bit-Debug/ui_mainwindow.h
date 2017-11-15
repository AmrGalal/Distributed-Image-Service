/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *sign_up_push_button;
    QPushButton *sign_in_push_button;
    QTextEdit *password_text_edit;
    QTextEdit *local_port_text_edit;
    QPushButton *bind_push_button;
    QTextEdit *username_text_edit;
    QTextEdit *server_ip_address_text_edit;
    QTextEdit *server_port_text_edit;
    QPushButton *sign_out_push_button;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(506, 469);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sign_up_push_button = new QPushButton(centralWidget);
        sign_up_push_button->setObjectName(QStringLiteral("sign_up_push_button"));
        sign_up_push_button->setGeometry(QRect(350, 60, 99, 27));
        sign_in_push_button = new QPushButton(centralWidget);
        sign_in_push_button->setObjectName(QStringLiteral("sign_in_push_button"));
        sign_in_push_button->setGeometry(QRect(350, 100, 99, 27));
        password_text_edit = new QTextEdit(centralWidget);
        password_text_edit->setObjectName(QStringLiteral("password_text_edit"));
        password_text_edit->setGeometry(QRect(170, 100, 171, 31));
        local_port_text_edit = new QTextEdit(centralWidget);
        local_port_text_edit->setObjectName(QStringLiteral("local_port_text_edit"));
        local_port_text_edit->setGeometry(QRect(20, 20, 121, 31));
        bind_push_button = new QPushButton(centralWidget);
        bind_push_button->setObjectName(QStringLiteral("bind_push_button"));
        bind_push_button->setGeometry(QRect(160, 20, 99, 27));
        username_text_edit = new QTextEdit(centralWidget);
        username_text_edit->setObjectName(QStringLiteral("username_text_edit"));
        username_text_edit->setGeometry(QRect(170, 60, 171, 31));
        server_ip_address_text_edit = new QTextEdit(centralWidget);
        server_ip_address_text_edit->setObjectName(QStringLiteral("server_ip_address_text_edit"));
        server_ip_address_text_edit->setGeometry(QRect(20, 60, 104, 31));
        server_port_text_edit = new QTextEdit(centralWidget);
        server_port_text_edit->setObjectName(QStringLiteral("server_port_text_edit"));
        server_port_text_edit->setGeometry(QRect(20, 100, 104, 31));
        sign_out_push_button = new QPushButton(centralWidget);
        sign_out_push_button->setObjectName(QStringLiteral("sign_out_push_button"));
        sign_out_push_button->setGeometry(QRect(350, 80, 99, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 506, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        sign_up_push_button->setText(QApplication::translate("MainWindow", "Sign Up", 0));
        sign_in_push_button->setText(QApplication::translate("MainWindow", "Sign In", 0));
        password_text_edit->setPlaceholderText(QApplication::translate("MainWindow", "Password", 0));
        local_port_text_edit->setPlaceholderText(QApplication::translate("MainWindow", "Local Port", 0));
        bind_push_button->setText(QApplication::translate("MainWindow", "Bind", 0));
        username_text_edit->setPlaceholderText(QApplication::translate("MainWindow", "Username", 0));
        server_ip_address_text_edit->setPlaceholderText(QApplication::translate("MainWindow", "Server IP", 0));
        server_port_text_edit->setPlaceholderText(QApplication::translate("MainWindow", "Server Port", 0));
        sign_out_push_button->setText(QApplication::translate("MainWindow", "Sign Out", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
