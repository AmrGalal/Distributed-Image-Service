#include <thread>
#include <future>
#include <chrono>
#include <mutex>
#include <fstream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

const std::string MainWindow::USERS_FILE_NAME = "users.txt";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->read_users();
    this->set_bind_widgets_visibility(true);
    this->set_start_widgets_visibility(false);
    this->set_logs_widgets_visibility(false);
    this->set_exit_widgets_visibility(false);
}

MainWindow::~MainWindow()
{
    delete this->ui;
    if (this->socket != NULL)
    {
        delete this->socket;
    }
}

// Auxiliary functions!
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

void MainWindow::log(const string & _log_message)
{
    this->ui->logs_list_widget->addItem(QString::fromStdString(_log_message));
}

// Visibility!
void MainWindow::set_widgets_visibility(const vector<QWidget*> _widgets, const bool _visibility)
{
    for (auto widget : _widgets)
    {
        widget->setVisible(_visibility);
    }
}
void MainWindow::set_logs_widgets_visibility(const bool _visibility)
{
    this->set_widgets_visibility(
    {
                    ui->logs_list_widget
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
void MainWindow::set_start_widgets_visibility(const bool _visibility){
    this->set_widgets_visibility(
    {
                    ui->start_push_button,
                },
                _visibility);
}
void MainWindow::set_exit_widgets_visibility(const bool _visibility){
    this->set_widgets_visibility(
    {
                    ui->exit_push_button
                },
                _visibility);
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
    this->set_start_widgets_visibility(true);
    this->show_message_box("Bind successful!");
}

void MainWindow::listen()
{
    while(true)
    {
        const auto received = this->socket->receive();
        const auto & request = received.first;
        const auto & address = received.second;
        this->users_mutex.lock();
        const string user_ip = std::string(inet_ntoa(address.sin_addr));
        const int user_port = ntohs(address.sin_port);
        Message * reply;
        switch(request.get_rpc_id())
        {
        case SignUpRequest:
        {
            const string username = request.get_username(), password = request.get_password();
            if (!this->users.insert(
                        make_pair(
                            username,
                            User(username, password, user_ip, user_port)
                            )).second)
            {
                reply = new Message(Error);
                reply->set_error_message("Username already exists!");
                this->log("Useranme: " + username + " already exists!");
            }
            else
            {
                reply = new Message(SignUpConfirmation);
                this->log("User: " + username + " successfully signed up!");
            }
        }
            break;
        case SignInRequest:
        {
            const string username = request.get_username(), password = request.get_password();
            auto iter = this->users.find(username);
            if (iter == this->users.end())
            {
                reply = new Message(Error);
                reply->set_error_message("Username does not exist!");
                this->log("Username " + username + " does not exist!");
            }
            else if (!iter->second.is_correct_password(password))
            {
                reply = new Message(Error);
                reply->set_error_message("Invalid password!");
                this->log("Invalid password for " + username + "!");
            }
            else
            {
                reply = new Message(SignInConfirmation);
                this->log("User " + username + "signed in successfully!");
            }
        }
        break;
        default:
            this->log("Received unexpected message type!");
        }
        this->users_mutex.unlock();
        this->socket->send(*reply, user_ip.c_str(), user_port);
        delete reply;
    }
}

void MainWindow::read_users()
{
    std::ifstream users_file;
    users_file.open(MainWindow::USERS_FILE_NAME);
    std::string line;
    while(getline(users_file, line))
    {
        User user = User(line);
        if (!this->users.insert(make_pair(user.get_username(), user)).second)
        {
            throw std::runtime_error("Repeated username in users file!");
        }
    }
    users_file.close();
    this->log("Successfully read " + std::to_string(this->users.size())  + " users information from file!");
}

void MainWindow::save_users()
{
    std::ofstream users_file;
    users_file.open(MainWindow::USERS_FILE_NAME);
    this->users_mutex.lock();
    for (auto user : this->users)
    {
        users_file << user.second.serialize() << endl;
    }
    users_file.close();
    this->log("Successfully saved " + std::to_string(this->users.size())  + " users information to file!");
    this->users_mutex.unlock();
}

void MainWindow::on_start_push_button_clicked()
{
    this->set_start_widgets_visibility(false);
    this->set_logs_widgets_visibility(true);
    this->set_exit_widgets_visibility(true);
    this->listening_thread = std::async(std::launch::async, &MainWindow::listen, this);
}

void MainWindow::on_exit_push_button_clicked()
{
    this->set_exit_widgets_visibility(false);
    this->set_logs_widgets_visibility(false);
    this->save_users();
    exit(0);
}
