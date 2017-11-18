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
#include <QtWidgets/QListWidget>
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
    QPushButton *bind_push_button;
    QLineEdit *local_port_line_edit;
    QListWidget *logs_list_widget;
    QPushButton *exit_push_button;
    QPushButton *start_push_button;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(531, 351);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        bind_push_button = new QPushButton(centralWidget);
        bind_push_button->setObjectName(QStringLiteral("bind_push_button"));
        bind_push_button->setGeometry(QRect(160, 10, 89, 25));
        local_port_line_edit = new QLineEdit(centralWidget);
        local_port_line_edit->setObjectName(QStringLiteral("local_port_line_edit"));
        local_port_line_edit->setGeometry(QRect(30, 10, 113, 25));
        logs_list_widget = new QListWidget(centralWidget);
        logs_list_widget->setObjectName(QStringLiteral("logs_list_widget"));
        logs_list_widget->setGeometry(QRect(30, 50, 481, 231));
        exit_push_button = new QPushButton(centralWidget);
        exit_push_button->setObjectName(QStringLiteral("exit_push_button"));
        exit_push_button->setGeometry(QRect(380, 10, 89, 25));
        start_push_button = new QPushButton(centralWidget);
        start_push_button->setObjectName(QStringLiteral("start_push_button"));
        start_push_button->setGeometry(QRect(270, 10, 89, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 531, 22));
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
        bind_push_button->setText(QApplication::translate("MainWindow", "Bind", Q_NULLPTR));
        local_port_line_edit->setPlaceholderText(QApplication::translate("MainWindow", "Local Port", Q_NULLPTR));
        exit_push_button->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        start_push_button->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
