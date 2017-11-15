/* Must handle the following:
 * - Unexpected messages received!
 * - Forever-blocking receive!
 */

#include "QMessageBox"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../Message.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(time(0));
    ui->setupUi(this);
    this->set_bind_widgets_visibility(true);
    this->set_sign_in_widgets_visibility(false);
    this->set_sign_out_widgets_visibility(false);
    this->set_send_widgets_visibility(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

string MainWindow::get_server_ip_address()
{
    return get_string_from_text_edit(ui->server_ip_address_text_edit).c_str();
}

int MainWindow::get_server_port()
{
    return atoi(get_string_from_text_edit(ui->server_port_text_edit).c_str());
}

void MainWindow::set_sign_in_widgets_visibility(bool visibility)
{
    ui->sign_in_push_button->setVisible(visibility);
    ui->sign_up_push_button->setVisible(visibility);
    ui->username_text_edit->setVisible(visibility);
    ui->password_text_edit->setVisible(visibility);
    ui->server_ip_address_text_edit->setVisible(visibility);
    ui->server_port_text_edit->setVisible(visibility);
}

void MainWindow::set_bind_widgets_visibility(bool visibility)
{
    ui->bind_push_button->setVisible(visibility);
}
void MainWindow::set_sign_out_widgets_visibility(bool visibility)
{
    ui->sign_out_push_button->setVisible(visibility);
}
void MainWindow::set_send_widgets_visibility(bool visibility)
{
}


void MainWindow::on_sign_up_push_button_clicked()
{
    Message sign_up_request(SignUpRequest);
    sign_up_request.setUsername(get_string_from_text_edit(ui->username_text_edit));
    sign_up_request.setPassword(get_string_from_text_edit(ui->password_text_edit));
    this->socket->send(
                sign_up_request,
                get_server_ip_address().c_str(),
                get_server_port());

    Message * response;
    sockaddr_in address;
    this->socket->receive(*response, address);

    switch(response->getRPCId())
    {
    case SignUpConfirmation:
        QMessageBox::information(
                    this,
                    QString::fromStdString("Sign up successful!"),
                    QString::fromStdString("You can now sign in to use the service!"));
        break;
    case Error:
        QMessageBox::information(
                    this,
                    QString::fromStdString("Sign up failed!"),
                    QString::fromStdString("Authentication error: " + response->getErrorMessage()));
        break;
    }
}

string MainWindow::get_string_from_text_edit(QTextEdit * text_edit)
{
    return text_edit->toPlainText().toStdString();
}

void MainWindow::on_bind_push_button_clicked()
{
    int local_port_number = atoi(get_string_from_text_edit(ui->local_port_text_edit).c_str());
    this->socket = new Socket(local_port_number);
    this->set_bind_widgets_visibility(false);
    this->set_sign_in_widgets_visibility(true);
}

void MainWindow::on_sign_in_push_button_clicked()
{
    Message sign_in_request(SignInRequest);
    sign_in_request.setUsername(get_string_from_text_edit(ui->username_text_edit));
    sign_in_request.setPassword(get_string_from_text_edit(ui->password_text_edit));
    this->socket->send(
                sign_in_request,
                get_server_ip_address().c_str(),
                get_server_port());

    Message * response;
    sockaddr_in address;
    this->socket->receive(*response, address);
    switch(response->getRPCId())
    {
    case SignInConfirmation:
        QMessageBox::information(
                    this,
                    QString::fromStdString("Sign in successful!"),
                    QString::fromStdString("You can now use the service!"));
        this->signed_in = true;
        this->set_send_widgets_visibility(true);
        break;
    case Error:
        QMessageBox::information(
                    this,
                    QString::fromStdString("Sign in failed!"),
                    QString::fromStdString("Authentication error: " + response->getErrorMessage()));
        break;
    }
}

void MainWindow::on_sign_out_push_button_clicked()
{
    this->signed_in = false;
    this->signed_in_username = "";
}
