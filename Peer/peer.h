#ifndef PEER_H
#define PEER_H

#include <set>
#include <mutex>
#include <future>

#include <QMainWindow>
#include <QLineEdit>

#include "../message.h"
#include "../socket.h"
#include <vector>
#include <ctime>
#include <map>

namespace Ui {
class Peer;
}

class Peer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Peer(QWidget *parent = 0);
    ~Peer();

private slots:
    void on_sign_up_push_button_clicked();

    void on_bind_push_button_clicked();

    void on_sign_in_push_button_clicked();

    void on_sign_out_push_button_clicked();

    void on_send_push_button_clicked();

private:
    // Visibility!
    void set_widgets_visibility(const std::vector<QWidget*> _widgets, const bool _visibility);
    void set_bind_widgets_visibility(const bool _visibility);
    void set_sign_in_widgets_visibility(const bool _visibility);
    void set_sign_out_widgets_visibility(const bool _visibility);
    void set_send_widgets_visibility(const bool _visibility);

    // Auxiliary functions!
    std::string get_string_from_line_edit(const QLineEdit * _line_edit, const bool _strict = true);
    void show_message_box(const std::string & _message_content, const std::string & _title = "Information");

    // Sending images!
    const static int MAX_IMAGE_CHUNK_SIZE = (1 << 10);
    static std::string file_to_string(const std::string & _file_path);
    static void string_to_file(const std::string & _file_path, const std::string & _file_content);
    void chunk_and_send_image(const std::string _image_id, const std::string _receiver_ip, const int _receiver_port);
    void  send_one_image_chunk(const std::string _image_id, const std::string _receiver_ip, const int _receiver_port, int _chunck_index_to_send);
    void checkImagePackets(map< std::pair<std::string,std::string> , std::pair<time_t,  map<int32_t,Message> > > &image_buffer2);
    void send_image(const std::string & _image_id);

    // GUI!
    Ui::Peer *ui;

    // My socket!
    Socket* socket;
    // Sign in, sign out and bind!
    bool signed_in = false;
    std::string username = "";
    std::string server_ip;
    int server_port;

    // Listening!
    void listen();

    // Image chunks buffer!
    void serve(std::pair<Message, sockaddr_in> _received);
    void send(const std::string & _image_id);
    std::future<void> listening_thread;
    std::map<std::pair<std::string, std::string>, std::vector<Message>> buffer;
    std::map< std::pair<std::string,std::string> , std::pair<time_t,  map<int32_t,Message> > > image_buffer2;
    std::mutex buffer_mutex;
};

#endif // PEER_H
