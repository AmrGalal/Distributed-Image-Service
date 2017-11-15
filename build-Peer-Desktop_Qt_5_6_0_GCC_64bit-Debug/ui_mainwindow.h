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
#include <QtWidgets/QLabel>
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
    QLabel *local_port_label;
    QPushButton *bind_push_button;
    QTextEdit *username_text_edit;
    QLabel *label;
    QLabel *label_2;
    QLabel *server_ip_address_label;
    QLabel *server_port_label;
    QTextEdit *server_ip_address_text_edit;
    QTextEdit *server_port_text_edit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(506, 343);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sign_up_push_button = new QPushButton(centralWidget);
        sign_up_push_button->setObjectName(QStringLiteral("sign_up_push_button"));
        sign_up_push_button->setGeometry(QRect(260, 160, 99, 27));
        sign_in_push_button = new QPushButton(centralWidget);
        sign_in_push_button->setObjectName(QStringLiteral("sign_in_push_button"));
        sign_in_push_button->setGeometry(QRect(260, 190, 99, 27));
        password_text_edit = new QTextEdit(centralWidget);
        password_text_edit->setObjectName(QStringLiteral("password_text_edit"));
        password_text_edit->setGeometry(QRect(120, 190, 121, 31));
        local_port_text_edit = new QTextEdit(centralWidget);
        local_port_text_edit->setObjectName(QStringLiteral("local_port_text_edit"));
        local_port_text_edit->setGeometry(QRect(120, 20, 121, 31));
        local_port_label = new QLabel(centralWidget);
        local_port_label->setObjectName(QStringLiteral("local_port_label"));
        local_port_label->setGeometry(QRect(20, 20, 71, 21));
        bind_push_button = new QPushButton(centralWidget);
        bind_push_button->setObjectName(QStringLiteral("bind_push_button"));
        bind_push_button->setGeometry(QRect(260, 20, 99, 27));
        username_text_edit = new QTextEdit(centralWidget);
        username_text_edit->setObjectName(QStringLiteral("username_text_edit"));
        username_text_edit->setGeometry(QRect(120, 150, 121, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 160, 71, 17));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 200, 67, 17));
        server_ip_address_label = new QLabel(centralWidget);
        server_ip_address_label->setObjectName(QStringLiteral("server_ip_address_label"));
        server_ip_address_label->setGeometry(QRect(20, 70, 131, 17));
        server_port_label = new QLabel(centralWidget);
        server_port_label->setObjectName(QStringLiteral("server_port_label"));
        server_port_label->setGeometry(QRect(20, 110, 121, 17));
        server_ip_address_text_edit = new QTextEdit(centralWidget);
        server_ip_address_text_edit->setObjectName(QStringLiteral("server_ip_address_text_edit"));
        server_ip_address_text_edit->setGeometry(QRect(160, 60, 104, 31));
        server_port_text_edit = new QTextEdit(centralWidget);
        server_port_text_edit->setObjectName(QStringLiteral("server_port_text_edit"));
        server_port_text_edit->setGeometry(QRect(160, 100, 104, 31));
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
        local_port_label->setText(QApplication::translate("MainWindow", "Local Port", 0));
        bind_push_button->setText(QApplication::translate("MainWindow", "Bind", 0));
        label->setText(QApplication::translate("MainWindow", "Username", 0));
        label_2->setText(QApplication::translate("MainWindow", "Password", 0));
        server_ip_address_label->setText(QApplication::translate("MainWindow", "Server IP Address", 0));
        server_port_label->setText(QApplication::translate("MainWindow", "Server Port", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
