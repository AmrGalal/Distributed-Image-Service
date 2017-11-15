#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

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
    void set_bind_widgets_visibility(bool visibility);
    void set_sign_in_widgets_visibility(bool visibility);
    void set_sign_out_widgets_visibility(bool visibility);
    void set_send_widgets_visibility(bool visibility);

    string get_string_from_text_edit(QTextEdit * text_edit);
    string get_server_ip_address();
    int get_server_port();

    Ui::MainWindow *ui;
    Socket *socket;
    bool socket_bound = false;
    bool signed_in = false;
    string signed_in_username = "";
};

#endif // MAINWINDOW_H
