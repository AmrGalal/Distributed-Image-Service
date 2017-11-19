/********************************************************************************
** Form generated from reading UI file 'peer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PEER_H
#define UI_PEER_H

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

class Ui_Peer
{
public:
    QWidget *centralWidget;
    QLineEdit *local_port_line_edit;
    QLineEdit *server_ip_line_edit;
    QLineEdit *server_port_line_edit;
    QLineEdit *username_line_edit;
    QLineEdit *password_line_edit;
    QPushButton *sign_up_push_button;
    QPushButton *sign_out_push_button;
    QPushButton *sign_in_push_button;
    QPushButton *bind_push_button;
    QPushButton *send_push_button;
    QLineEdit *receiver_ip_line_edit;
    QLineEdit *receiver_port_line_edit;
    QLineEdit *image_id_line_edit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Peer)
    {
        if (Peer->objectName().isEmpty())
            Peer->setObjectName(QStringLiteral("Peer"));
        Peer->resize(658, 453);
        centralWidget = new QWidget(Peer);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        local_port_line_edit = new QLineEdit(centralWidget);
        local_port_line_edit->setObjectName(QStringLiteral("local_port_line_edit"));
        local_port_line_edit->setGeometry(QRect(20, 10, 113, 25));
        server_ip_line_edit = new QLineEdit(centralWidget);
        server_ip_line_edit->setObjectName(QStringLiteral("server_ip_line_edit"));
        server_ip_line_edit->setGeometry(QRect(20, 50, 113, 25));
        server_port_line_edit = new QLineEdit(centralWidget);
        server_port_line_edit->setObjectName(QStringLiteral("server_port_line_edit"));
        server_port_line_edit->setGeometry(QRect(20, 90, 113, 25));
        username_line_edit = new QLineEdit(centralWidget);
        username_line_edit->setObjectName(QStringLiteral("username_line_edit"));
        username_line_edit->setGeometry(QRect(150, 50, 113, 25));
        password_line_edit = new QLineEdit(centralWidget);
        password_line_edit->setObjectName(QStringLiteral("password_line_edit"));
        password_line_edit->setGeometry(QRect(150, 90, 113, 25));
        sign_up_push_button = new QPushButton(centralWidget);
        sign_up_push_button->setObjectName(QStringLiteral("sign_up_push_button"));
        sign_up_push_button->setGeometry(QRect(280, 50, 89, 25));
        sign_out_push_button = new QPushButton(centralWidget);
        sign_out_push_button->setObjectName(QStringLiteral("sign_out_push_button"));
        sign_out_push_button->setGeometry(QRect(280, 70, 89, 25));
        sign_in_push_button = new QPushButton(centralWidget);
        sign_in_push_button->setObjectName(QStringLiteral("sign_in_push_button"));
        sign_in_push_button->setGeometry(QRect(280, 90, 89, 25));
        bind_push_button = new QPushButton(centralWidget);
        bind_push_button->setObjectName(QStringLiteral("bind_push_button"));
        bind_push_button->setGeometry(QRect(280, 10, 89, 25));
        send_push_button = new QPushButton(centralWidget);
        send_push_button->setObjectName(QStringLiteral("send_push_button"));
        send_push_button->setGeometry(QRect(410, 130, 89, 25));
        receiver_ip_line_edit = new QLineEdit(centralWidget);
        receiver_ip_line_edit->setObjectName(QStringLiteral("receiver_ip_line_edit"));
        receiver_ip_line_edit->setGeometry(QRect(20, 130, 113, 25));
        receiver_port_line_edit = new QLineEdit(centralWidget);
        receiver_port_line_edit->setObjectName(QStringLiteral("receiver_port_line_edit"));
        receiver_port_line_edit->setGeometry(QRect(150, 130, 113, 25));
        image_id_line_edit = new QLineEdit(centralWidget);
        image_id_line_edit->setObjectName(QStringLiteral("image_id_line_edit"));
        image_id_line_edit->setGeometry(QRect(280, 130, 113, 25));
        Peer->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Peer);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 658, 22));
        Peer->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Peer);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Peer->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Peer);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Peer->setStatusBar(statusBar);

        retranslateUi(Peer);

        QMetaObject::connectSlotsByName(Peer);
    } // setupUi

    void retranslateUi(QMainWindow *Peer)
    {
        Peer->setWindowTitle(QApplication::translate("Peer", "Peer", Q_NULLPTR));
        local_port_line_edit->setPlaceholderText(QApplication::translate("Peer", "Local Port", Q_NULLPTR));
        server_ip_line_edit->setPlaceholderText(QApplication::translate("Peer", "Server IP", Q_NULLPTR));
        server_port_line_edit->setPlaceholderText(QApplication::translate("Peer", "Server Port", Q_NULLPTR));
        username_line_edit->setPlaceholderText(QApplication::translate("Peer", "Username", Q_NULLPTR));
        password_line_edit->setPlaceholderText(QApplication::translate("Peer", "Password", Q_NULLPTR));
        sign_up_push_button->setText(QApplication::translate("Peer", "Sign Up", Q_NULLPTR));
        sign_out_push_button->setText(QApplication::translate("Peer", "Sign Out", Q_NULLPTR));
        sign_in_push_button->setText(QApplication::translate("Peer", "Sign In", Q_NULLPTR));
        bind_push_button->setText(QApplication::translate("Peer", "Bind", Q_NULLPTR));
        send_push_button->setText(QApplication::translate("Peer", "Send", Q_NULLPTR));
        receiver_ip_line_edit->setPlaceholderText(QApplication::translate("Peer", "Receiver IP", Q_NULLPTR));
        receiver_port_line_edit->setPlaceholderText(QApplication::translate("Peer", "Receiver Port", Q_NULLPTR));
        image_id_line_edit->setPlaceholderText(QApplication::translate("Peer", "Image Id", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Peer: public Ui_Peer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PEER_H
