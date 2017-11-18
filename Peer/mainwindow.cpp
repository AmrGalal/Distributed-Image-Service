/* Must handle the following:
 * - Unexpected messages received!
 * - Forever-blocking receive!
 */

#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "QMessageBox"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../Message.h"

// Construction!
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->set_bind_widgets_visibility(true);
    this->set_sign_in_widgets_visibility(false);
    this->set_sign_out_widgets_visibility(false);
    this->set_send_widgets_visibility(false);
}

MainWindow::~MainWindow()
{
    delete this->ui;
    delete this->socket;
}

// Auxiliary funcions!
string MainWindow::get_string_from_line_edit(const QLineEdit * _line_edit, const bool _strict)
{
/* Args:
 * line_edit: LineEdit Object to retrieve text from.
 * strict: If true, the LineEdit object must be nonempty.
 */
    string ans = _line_edit->text().toStdString();
    if (_strict && ans.empty())
    {
        throw std::runtime_error("Unexpected empty LineEdit! Did you forget to fill in some needed information?");
    }
    return ans;
}

void MainWindow::show_message_box(const string & message_content, const string & title)
{
    QMessageBox::information(
                this,
                QString::fromStdString(title),
                QString::fromStdString(message_content));
}

// Visibility modifiers!
void MainWindow::set_widgets_visibility(const vector<QWidget*> _widgets, const bool _visibility)
{
    for (auto widget : _widgets)
    {
        widget->setVisible(_visibility);
    }
}

void MainWindow::set_sign_in_widgets_visibility(const bool _visibility)
{
    this->set_widgets_visibility(
    {
                    ui->sign_in_push_button,
                    ui->sign_up_push_button,
                    ui->username_line_edit,
                    ui->password_line_edit,
                    ui->server_ip_line_edit,
                    ui->server_port_line_edit
                },
                _visibility);
}

void MainWindow::set_bind_widgets_visibility(const bool _visibility)
{
    this->set_widgets_visibility(
    {
                    ui->bind_push_button,
                    ui->local_port_line_edit
                },
                _visibility);
}

void MainWindow::set_sign_out_widgets_visibility(bool _visibility)
{
    this->set_widgets_visibility(
    {
                    ui->sign_out_push_button
                },
                _visibility);
}

void MainWindow::set_send_widgets_visibility(bool _visibility)
{
}

// Events!
void MainWindow::on_bind_push_button_clicked()
{
    const int local_port_number = atoi(get_string_from_line_edit(ui->local_port_line_edit).c_str());
    try {
        this->socket = new Socket(local_port_number);
    }
    catch (const exception & e)
    {
        this->show_message_box(e.what());
        return;
    }
    this->set_bind_widgets_visibility(false);
    this->set_sign_in_widgets_visibility(true);
    this->show_message_box("Bind successful!");
}

void MainWindow::on_sign_up_push_button_clicked()
{
    Message sign_up_request(SignUpRequest);
    const string username = get_string_from_line_edit(ui->username_line_edit);
    const string password = get_string_from_line_edit(ui->password_line_edit);
    const string server_ip = get_string_from_line_edit(ui->server_ip_line_edit);
    const int server_port = atoi(get_string_from_line_edit(ui->server_port_line_edit).c_str());
    sign_up_request.setUsername(username);
    sign_up_request.setPassword(password);
    this->socket->send(sign_up_request, server_ip.c_str(), server_port);

    Message reply(Error);
    sockaddr_in address;
    this->socket->receive(reply, address);

    switch(reply.getRPCId())
    {
    case SignUpConfirmation:
        this->show_message_box("Sign Up Successful!");
        break;
    case Error:
        this->show_message_box("Authentication error: " + reply.getErrorMessage());
        break;
     default:
        this->show_message_box("Unexpected message received!");
        break;
    }
}

void MainWindow::on_sign_in_push_button_clicked()
{
    // Get sign-in information from widgets!
    const string username = get_string_from_line_edit(ui->username_line_edit);
    const string password = get_string_from_line_edit(ui->password_line_edit);
    const string server_ip = get_string_from_line_edit(ui->server_ip_line_edit);
    const int server_port = atoi(get_string_from_line_edit(ui->server_port_line_edit).c_str());

    // Request sign-in!
    Message sign_in_request(SignInRequest);
    sign_in_request.setUsername(username);
    sign_in_request.setPassword(password);
    this->socket->send(sign_in_request, server_ip.c_str(), server_port);

    // Wait for reply!
    Message reply(Error);
    sockaddr_in address;
    this->socket->receive(reply, address);
    switch(reply.getRPCId())
    {
    case SignInConfirmation:
        sign_in(username, server_ip, server_port);
        break;
    case Error:
        this->show_message_box("Authentication error: " + reply.getErrorMessage());
        break;
    default:
        this->show_message_box("Unexpected message received!");
        break;
    }
}

void MainWindow::on_sign_out_push_button_clicked()
{
    Message sign_out_request(SignOutRequest);
    sign_out_request.setUsername(this->username);
    this->socket->send(
                sign_out_request,
                this->server_ip.c_str(),
                this->server_port);
    sign_out();
}

// Sign-in, sing-out and bind!
void MainWindow::sign_in(const string & _username, const string & _server_ip, const int _server_port)
{
    this->signed_in = true;
    this->username = _username;
    this->server_ip = _server_ip;
    this->server_port = _server_port;
    this->set_sign_in_widgets_visibility(false);
    this->set_send_widgets_visibility(true);
    this->set_sign_out_widgets_visibility(true);
    this->show_message_box("Sign in successful!");
}

void MainWindow::sign_out(){
    this->signed_in = false;
    this->username = "";
    this->server_ip = "";
    this->server_port = 0;
    this->set_sign_out_widgets_visibility(false);
    this->set_send_widgets_visibility(false);
    this->set_sign_in_widgets_visibility(true);
    this->show_message_box("Sign out successful!");
}
