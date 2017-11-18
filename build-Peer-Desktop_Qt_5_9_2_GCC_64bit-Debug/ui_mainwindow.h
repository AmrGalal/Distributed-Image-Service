/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *sign_up_push_button;
    QPushButton *sign_in_push_button;
    QPushButton *bind_push_button;
    QPushButton *sign_out_push_button;
    QLineEdit *local_port_line_edit;
    QLineEdit *server_ip_line_edit;
    QLineEdit *server_port_line_edit;
    QLineEdit *username_line_edit;
    QLineEdit *password_line_edit;
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
        bind_push_button = new QPushButton(centralWidget);
        bind_push_button->setObjectName(QStringLiteral("bind_push_button"));
        bind_push_button->setGeometry(QRect(160, 20, 99, 27));
        sign_out_push_button = new QPushButton(centralWidget);
        sign_out_push_button->setObjectName(QStringLiteral("sign_out_push_button"));
        sign_out_push_button->setGeometry(QRect(350, 80, 99, 27));
        local_port_line_edit = new QLineEdit(centralWidget);
        local_port_line_edit->setObjectName(QStringLiteral("local_port_line_edit"));
        local_port_line_edit->setGeometry(QRect(20, 20, 113, 25));
        server_ip_line_edit = new QLineEdit(centralWidget);
        server_ip_line_edit->setObjectName(QStringLiteral("server_ip_line_edit"));
        server_ip_line_edit->setGeometry(QRect(20, 60, 113, 25));
        server_port_line_edit = new QLineEdit(centralWidget);
        server_port_line_edit->setObjectName(QStringLiteral("server_port_line_edit"));
        server_port_line_edit->setGeometry(QRect(20, 100, 113, 25));
        username_line_edit = new QLineEdit(centralWidget);
        username_line_edit->setObjectName(QStringLiteral("username_line_edit"));
        username_line_edit->setGeometry(QRect(160, 60, 171, 25));
        password_line_edit = new QLineEdit(centralWidget);
        password_line_edit->setObjectName(QStringLiteral("password_line_edit"));
        password_line_edit->setGeometry(QRect(160, 100, 171, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 506, 22));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        sign_up_push_button->setText(QApplication::translate("MainWindow", "Sign Up", Q_NULLPTR));
        sign_in_push_button->setText(QApplication::translate("MainWindow", "Sign In", Q_NULLPTR));
        bind_push_button->setText(QApplication::translate("MainWindow", "Bind", Q_NULLPTR));
        sign_out_push_button->setText(QApplication::translate("MainWindow", "Sign Out", Q_NULLPTR));
        local_port_line_edit->setPlaceholderText(QApplication::translate("MainWindow", "Local Port", Q_NULLPTR));
        server_ip_line_edit->setPlaceholderText(QApplication::translate("MainWindow", "Server IP", Q_NULLPTR));
        server_port_line_edit->setPlaceholderText(QApplication::translate("MainWindow", "Server Port", Q_NULLPTR));
        username_line_edit->setPlaceholderText(QApplication::translate("MainWindow", "Username", Q_NULLPTR));
        password_line_edit->setPlaceholderText(QApplication::translate("MainWindow", "Password", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
