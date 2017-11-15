#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../Message.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(time(0));
    ui->setupUi(this);
    this->set_sign_up_widgets_visibility(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_sign_up_widgets_visibility(bool visibility)
{
    ui->sign_in_push_button->setVisible(visibility);
    ui->sign_up_push_button->setVisible(visibility);
    ui->username_text_edit->setVisible(visibility);
    ui->password_text_edit->setVisible(visibility);
    ui->server_ip_address_text_edit->setVisible(visibility);
    ui->server_port_text_edit->setVisible(visibility);
}

void MainWindow::on_sign_up_push_button_clicked()
{
    Message m(SignUpRequest);
    m.setUsername(get_string_from_text_edit(ui->username_text_edit));
    m.setPassword(get_string_from_text_edit(ui->password_text_edit));
    this->socket->send(
                m,
                get_string_from_text_edit(ui->server_ip_address_text_edit).c_str(),
                atoi(get_string_from_text_edit(ui->server_port_text_edit).c_str()));
}

string MainWindow::get_string_from_text_edit(QTextEdit * text_edit)
{
    return text_edit->toPlainText().toStdString();
}

void MainWindow::on_bind_push_button_clicked()
{
    if(!this->socket_bound)
    {
        int local_port_number = atoi(get_string_from_text_edit(ui->local_port_text_edit).c_str());
        this->socket = new Socket(local_port_number);
        this->socket_bound = true;
        this->set_sign_up_widgets_visibility(true);
    }
    else
    {
        // You should show a MessageBox!
    }
}

void MainWindow::on_sign_in_push_button_clicked()
{

}
