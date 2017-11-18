#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

#include "../Socket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_sign_up_push_button_clicked();

    void on_bind_push_button_clicked();

    void on_sign_in_push_button_clicked();

    void on_sign_out_push_button_clicked();

private:
    // Visibility!
    void set_widgets_visibility(const vector<QWidget*> _widgets, const bool _visibility);
    void set_bind_widgets_visibility(const bool _visibility);
    void set_sign_in_widgets_visibility(const bool _visibility);
    void set_sign_out_widgets_visibility(const bool _visibility);
    void set_send_widgets_visibility(const bool _visibility);

    // Auxiliary functions!
    string get_string_from_line_edit(const QLineEdit * _line_edit, const bool _strict = true);
    void show_message_box(const string & _message_content, const string & _title = "Information");

    // GUI!
    Ui::MainWindow *ui;

    // My socket!
    Socket* socket;
    // Sign in, sign out and bind!
    void sign_in(const string & _username, const string & _server_ip, const int _server_port);
    void sign_out();
    bool signed_in = false;
    string username = "";
    string server_ip;
    int server_port;
};

#endif // MAINWINDOW_H
