#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

#include "Socket.h"

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

private:
    Ui::MainWindow *ui;
    Socket *socket;
    bool socket_bound = false;
    void set_sign_up_widgets_visibility(bool visibility);
    string get_string_from_text_edit(QTextEdit * text_edit);
};

#endif // MAINWINDOW_H
