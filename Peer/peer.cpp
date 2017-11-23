/* Be careful not to send parameters to threads by reference!
 */

#include <algorithm>
#include <fstream>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <QMessageBox>
#include <iostream>
#include <map>
#include <string>
#include<ctime>
#include <algorithm>
#include "peer.h"
#include "ui_peer.h"
#include "../message.h"
//using namespace  std;
// Construction!
Peer::Peer(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::Peer)
{
    ui->setupUi(this);
    this->set_bind_widgets_visibility(true);
    this->set_sign_in_widgets_visibility(false);
    this->set_sign_out_widgets_visibility(false);
    // this->set_send_widgets_visibility(false);
}

Peer::~Peer()
{
    delete this->ui;
    delete this->socket;
}

// Auxiliary funcions!
string Peer::get_string_from_line_edit(const QLineEdit * _line_edit, const bool _strict)
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

void Peer::show_message_box(const string & message_content, const string & title)
{
    QMessageBox::information(
                             this,
                             QString::fromStdString(title),
                             QString::fromStdString(message_content));
}

// Visibility modifiers!
void Peer::set_widgets_visibility(const vector<QWidget*> _widgets, const bool _visibility)
{
    for (auto widget : _widgets)
    {
        widget->setVisible(_visibility);
    }
}

void Peer::set_sign_in_widgets_visibility(const bool _visibility)
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

void Peer::set_bind_widgets_visibility(const bool _visibility)
{
    this->set_widgets_visibility(
                                 {
                                     ui->bind_push_button,
                                     ui->local_port_line_edit
                                 },
                                 _visibility);
}

void Peer::set_sign_out_widgets_visibility(bool _visibility)
{
    this->set_widgets_visibility(
                                 {
                                     ui->sign_out_push_button
                                 },
                                 _visibility);
}

void Peer::set_send_widgets_visibility(bool _visibility)
{
    this->set_widgets_visibility(
                                 {
                                     ui->send_push_button,
                                     ui->image_id_line_edit,
                                     ui->receiver_ip_line_edit,
                                     ui->receiver_port_line_edit
                                 },
                                 _visibility);
}

// Events!
void Peer::on_bind_push_button_clicked()
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

void Peer::on_sign_up_push_button_clicked()
{
    Message sign_up_request(SignUpRequest);
    const string username = get_string_from_line_edit(ui->username_line_edit);
    const string password = get_string_from_line_edit(ui->password_line_edit);
    const string server_ip = get_string_from_line_edit(ui->server_ip_line_edit);
    const int server_port = atoi(get_string_from_line_edit(ui->server_port_line_edit).c_str());
    sign_up_request.set_username(username);
    sign_up_request.set_password(password);
    this->socket->send(sign_up_request, server_ip.c_str(), server_port);
    
    const auto received = this->socket->receive();
    const auto & reply = received.first;
    const auto & address = received.second;
    
    switch(reply.get_rpc_id())
    {
        case SignUpConfirmation:
            this->show_message_box("Sign Up Successful!");
            break;
        case Error:
            this->show_message_box("Authentication error: " + reply.get_error_message());
            break;
        default:
            this->show_message_box("Unexpected message received!");
            break;
    }
}

void Peer::on_sign_in_push_button_clicked()
{
    // Get sign-in information from widgets!
    const string username = get_string_from_line_edit(ui->username_line_edit);
    const string password = get_string_from_line_edit(ui->password_line_edit);
    const string server_ip = get_string_from_line_edit(ui->server_ip_line_edit);
    const int server_port = atoi(get_string_from_line_edit(ui->server_port_line_edit).c_str());
    
    // Request sign-in!
    Message sign_in_request(SignInRequest);
    sign_in_request.set_username(username);
    sign_in_request.set_password(password);
    this->socket->send(sign_in_request, server_ip.c_str(), server_port);
    
    // Wait for reply!
    const auto received = this->socket->receive();
    const auto & reply = received.first;
    const auto & address = received.second;
    
    switch(reply.get_rpc_id())
    {
        case SignInConfirmation:
            this->signed_in = true;
            this->username = username;
            this->server_ip = server_ip;
            this->server_port = server_port;
            this->set_sign_in_widgets_visibility(false);
            this->set_send_widgets_visibility(true);
            this->set_sign_out_widgets_visibility(true);
            this->show_message_box("Sign in successful!");
            this->listening_thread = async(launch::async, &Peer::listen, this);
            break;
        case Error:
            this->show_message_box("Authentication error: " + reply.get_error_message());
            break;
        default:
            this->show_message_box("Unexpected message received! Was Expecting SignInConfirmation!");
            break;
    }
}

void Peer::on_sign_out_push_button_clicked()
{
    Message sign_out_request(SignOutRequest);
    sign_out_request.set_username(this->username);
    this->socket->send(
                       sign_out_request,
                       this->server_ip.c_str(),
                       this->server_port);
    this->signed_in = false;
    this->username = "";
    this->server_ip = "";
    this->server_port = 0;
    this->set_sign_out_widgets_visibility(false);
    this->set_send_widgets_visibility(false);
    this->set_sign_in_widgets_visibility(true);
    this->show_message_box("Sign out successful!");
    exit(0);
}

// Sending images!

std::string Peer::file_to_string(const std::string & _file_path){
    std::ifstream input_file;
    input_file.open(_file_path.c_str(), std::ios::in|std::ios::binary|std::ios::ate);
    std::ifstream::pos_type size = input_file.tellg();
    input_file.seekg(0, std::ios::beg);
    char * data = new char[size];
    input_file.read(data, size);
    std::string ans;
    for (int i = 0; i < size; ++i) ans += std::string(1, data[i]);
    delete data;
    input_file.close();
    return ans;
}
void Peer::string_to_file(const std::string & _file_path, const std::string & _file_content){
    std::ofstream output_file;
    output_file.open(_file_path.c_str(), std::ofstream::binary);
    output_file.write(_file_content.c_str(), _file_content.length());
    output_file.close();
}

void Peer::chunk_and_send_image(const std::string _image_id, const std::string _receiver_ip, const int _receiver_port) {
    const std::string image_data = Peer::file_to_string(_image_id);
    const int num_chunks = image_data.length() / Peer::MAX_IMAGE_CHUNK_SIZE
    + bool(image_data.length() % Peer::MAX_IMAGE_CHUNK_SIZE);
    std::vector<Message> ans;
    for (int i = 0; i < num_chunks; ++i)
    {
        Message image_chunk(ImageChunk);
        image_chunk.set_image_id(_image_id);
        image_chunk.set_image_chunk_index(i);
        image_chunk.set_image_num_chunks(num_chunks);
        image_chunk.set_image_chunk_content(image_data.substr(i * Peer::MAX_IMAGE_CHUNK_SIZE, Peer::MAX_IMAGE_CHUNK_SIZE));
        // usleep(10000);
        std::cout << "Sending packet of " << i << std::endl;
        this->socket->send(image_chunk, _receiver_ip.c_str(), _receiver_port);
    }
}


void  Peer::send_one_image_chunk(const std::string _image_id, const std::string _receiver_ip, const int _receiver_port, int _chunck_index_to_send) {
    const std::string image_data =  file_to_string(_image_id);
    const int num_chunks = image_data.length() /  MAX_IMAGE_CHUNK_SIZE
    + bool(image_data.length() %  MAX_IMAGE_CHUNK_SIZE);
    std::vector<Message> ans;
    Message image_chunk(ImageChunk);
    image_chunk.set_image_id(_image_id);
    image_chunk.set_image_chunk_index(_chunck_index_to_send);
    image_chunk.set_image_num_chunks(num_chunks);
    image_chunk.set_image_chunk_content(image_data.substr(_chunck_index_to_send *  MAX_IMAGE_CHUNK_SIZE,  MAX_IMAGE_CHUNK_SIZE));
    this->socket->send(image_chunk, _receiver_ip.c_str(), _receiver_port);
    
}
void  Peer::send_one_image_chunk_request(const std::string _image_id, const std::string _receiver_ip, const int _receiver_port, int _chunck_index_to_send) {
//    const std::string image_data =  file_to_string(_image_id);
//    const int num_chunks = image_data.length() /  MAX_IMAGE_CHUNK_SIZE
//    + bool(image_data.length() %  MAX_IMAGE_CHUNK_SIZE);
//    std::vector<Message> ans;
    Message image_chunk(oneChunkRequested);
    image_chunk.set_image_id(_image_id);
    image_chunk.set_image_chunk_index(_chunck_index_to_send);
//    image_chunk.set_image_num_chunks(num_chunks);
//    image_chunk.set_image_chunk_content(image_data.substr(_chunck_index_to_send *  MAX_IMAGE_CHUNK_SIZE,  MAX_IMAGE_CHUNK_SIZE));
    this->socket->send(image_chunk, _receiver_ip.c_str(), _receiver_port);

}
//receives & saves if complete receival happend
void Peer::serve(std::pair<Message, sockaddr_in> _received)
{
    //const auto &
    Message message = _received.first;
    const auto & address = _received.second;
    switch (message.get_rpc_id()) {
        case ImageChunk:
        {
            this->buffer_mutex.lock();
        std::cout<<"saving packets"<<std::endl;
            std::string ip_and_port_concat=std::string(inet_ntoa(address.sin_addr))+std::string("*")+std::string(to_string(ntohs(address.sin_port)));
            const auto key = make_pair(
                                       ip_and_port_concat, message.get_image_id());
     //LOL
            if(image_buffer2.find(key) == image_buffer2.end())
            {
                time_t time2;  time2=time(0);
                image_buffer2.insert(
                                     make_pair( key,
                                               make_pair(time2, map<int32_t, Message>())
                                               ) );
                image_buffer2.find(key)->second.second.insert(make_pair(message.get_image_chunk_index(), message));
            }
            else{
                image_buffer2.find(key)->second.second.insert(make_pair(message.get_image_chunk_index(), message));
            }
            
            if(image_buffer2.find(key)->second.second.size()==message.get_image_num_chunks()){
                string image_data = "";
                map<int32_t, Message> temp=image_buffer2.find(key)->second.second;
                for ( int i=0;i<message.get_image_num_chunks();i++)
                {
                    image_data += temp.find(i)->second.get_image_chunk_content();
                }
                std::cout<<"size 2bl delete"<<image_buffer2.size()<<std::endl;
                
                string_to_file("received_" + message.get_image_id(), image_data);
                auto itr2=image_buffer2.find(key);
                image_buffer2.erase(itr2);
                std::cout<<"size after delete"<<image_buffer2.size()<<std::endl;
                std::cout<<"Save Success inside SERVE  fun \n";
            }
            this->buffer_mutex.unlock();
        }
            break;
        case oneChunkRequested:
        {

            //send ?!!!
            //🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨🚨 usually received but we're gonna send, what abt spanning a thread ?!!
            // int chunck_index_to_be_requested=message.get_image_chunk_index();

        // fff

        std::string currentIp=std::string(inet_ntoa(address.sin_addr));
        int stupidPortN=ntohs(address.sin_port);
      //  cout << "Port number receiving " << stupidPortN << std::endl;
        //image_buffer2[]

        //serve(make_pair(requestChunk,v));
        send_one_image_chunk( message.get_image_id(),
                              currentIp,
                              stupidPortN, message.get_image_chunk_index());

       }
            break;
        default:
            break;
    }
}


void Peer:: checkImagePackets(map< std::pair<std::string,std::string> , std::pair<time_t,  map<int32_t,Message> > > &image_buffer2){
    while(1){
        usleep(2000000);

        cout << "Worker thread waiting for the lock \n";
        buffer_mutex.lock();
        cout << "Worker thread got the lock \n";
        
        for(auto &p:image_buffer2){
            time_t  timer2= time(0);
            auto &cur_chunk_map= p.second.second;
            cout<<"curr size"<<cur_chunk_map.size()<<"expected"<<cur_chunk_map.begin()->second.get_image_num_chunks()<<std::endl;
            cout<<"diff "<<difftime(timer2,p.second.first)<<std::endl;
           
            string curr_ip_address=p.first.first;
            string curr_image_id=p.first.second;
            
            if(difftime(timer2,p.second.first)>=0)
                cout<<"Numbers of secs passed since 1st packet insertion" << difftime(timer2,p.second.first) << std::endl;
            
            if (difftime(timer2,p.second.first)>=100 &&!cur_chunk_map.empty() &&
                cur_chunk_map.size()<cur_chunk_map.begin()->second.get_image_num_chunks())
            {
                //image_buffer2.find(make_pair(curr_ip_address, curr_image_id))->second.second.size()<<endl
                auto itr2=image_buffer2.find(make_pair(curr_ip_address, curr_image_id));
                image_buffer2.erase(itr2);

                //delete this entry
                //>=5
                std::cout <<"deleting";
            }
            else if( (difftime(timer2,p.second.first)) >=10 && (!cur_chunk_map.empty())
                    && (cur_chunk_map.size()<cur_chunk_map.begin()->second.get_image_num_chunks()) ){
                
                //ask for re-send
                for(int i=0;i<cur_chunk_map.begin()->second.get_image_num_chunks();i++)
                {
                    std::cout << "In the CheckImage thread iteration of i = " << i << "from " << cur_chunk_map.begin()->second.get_image_num_chunks() << std::endl;
                    std::cout<<"MISSING PACKETS OCCURRING \n";
                    if(! cur_chunk_map.count(i)){
                        //ask for this packet
                        Message requestChunk(oneChunkRequested);
                        requestChunk.set_image_id(p.first.second);
                        requestChunk.set_image_chunk_index(i);
                        std::string currentIp=p.first.first;
                        std::string stupidPortN=currentIp.substr((currentIp.find('*')+1));
                        std::cout << "Port number " << stupidPortN << std::endl;
                        //image_buffer2[]
                        sockaddr_in v;
                        buffer_mutex.unlock();
                        //serve(make_pair(requestChunk,v));
                        string m = requestChunk.get_image_id();
                        //send_one_image_chunk_request
                        send_one_image_chunk_request( requestChunk.get_image_id(),
                                              currentIp.substr(0,currentIp.find('*')),
                                              stoi(stupidPortN.c_str()), requestChunk.get_image_chunk_index());
                        
                        buffer_mutex.lock();
                        // requestChunk.marshal();
                        //send
                    }
                    std::cout<<"size p.s"<<image_buffer2.find(make_pair(curr_ip_address, curr_image_id))->second.second.size()<<std::endl;
                    std::cout<<"total size"<<cur_chunk_map.begin()->second.get_image_num_chunks()<<std::endl;
                    
                    
                }
                std::cout << "exited this for loop \n";
                if(image_buffer2.find(make_pair(curr_ip_address, curr_image_id))->second.second.size()==cur_chunk_map.begin()->second.get_image_num_chunks()){
                    string image_data_str = "";
                    std::cout << "Saving to the file \n";
                    //map<int32_t, Message> temp=image_buffer2.find(make_pair(p , idd ))->second.second;
                    for ( int i=0;i<cur_chunk_map.begin()->second.get_image_num_chunks();i++)
                    {
                        image_data_str += image_buffer2.find(make_pair(curr_ip_address, curr_image_id))->second.second[i].get_image_chunk_content();
                    }
                   // std::cout<<"size 2bl delete"<<image_buffer2.size()<<endl;
                    
                    string_to_file("received_" + p.first.second, image_data_str);
                    //                        auto itr2=image_buffer2.find(make_pair(p,idd));
                    //                        image_buffer2.erase(itr2);
                    std::cout<<"IMAGE SAVED SUCCESSFULLY"<<std::endl;
                }
            }
            else if( (difftime(timer2,p.second.first)) >=10 && (!cur_chunk_map.empty())
                    && image_buffer2.find(make_pair(curr_ip_address, curr_image_id))->second.second.size()==cur_chunk_map.begin()->second.get_image_num_chunks() ){
                string image_data_str = "";
                std::cout << "Saving to the file \n";
                //map<int32_t, Message> temp=image_buffer2.find(make_pair(p , idd ))->second.second;
                for ( int i=0;i<cur_chunk_map.begin()->second.get_image_num_chunks();i++)
                {
                    image_data_str += image_buffer2.find(make_pair(curr_ip_address, curr_image_id))->second.second[i].get_image_chunk_content();
                }
               // cout<<"size 2bl delete"<<image_buffer2.size()<<endl;

                string_to_file("received_" + p.first.second, image_data_str);
                //                        auto itr2=image_buffer2.find(make_pair(p,idd));
                //                        image_buffer2.erase(itr2);
                std::cout<<"IMAGE SAVED SUCCESSFULLY"<<std::endl;


            }
        }
        buffer_mutex.unlock();
        std::cout << "Worker thread released the lock \n";
        
    }
    
}


void Peer::listen()
{
    auto handle = std::async(std::launch::async,&Peer::checkImagePackets, this,ref(this->image_buffer2));
    while(true)
    {
        // auto serving_thread = async(launch::async, &Peer::serve, this, this->socket->receive());
        this->serve(this->socket->receive());
    }
}

void Peer::on_send_push_button_clicked()
{
    this->chunk_and_send_image(get_string_from_line_edit(ui->image_id_line_edit),
                               get_string_from_line_edit(ui->receiver_ip_line_edit),
                               atoi(get_string_from_line_edit(ui->receiver_port_line_edit).c_str()));
}
