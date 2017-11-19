#include <string>
#include <vector>
#include <stdexcept>

#include <arpa/inet.h>

#include "message.h"

// Constructor and destructor.
Message::Message (RPCId _rpc_id)
{
    this->rpc_id = _rpc_id;
}
Message::~Message ()
{
}

// Marshalling Logic.
Message::Message (const char * _marshalled_message)
{
    this->rpc_id = (RPCId) Message::deserialize_int(_marshalled_message);
    switch(this->rpc_id)
    {
    case SignUpRequest:
    case SignInRequest:
        this->set_username(Message::read_length_prepended_string(_marshalled_message));
        this->set_password(Message::read_length_prepended_string(_marshalled_message));
        break;
    case SignUpConfirmation:
    case SignInConfirmation:
        break;
    case SignOutRequest:
        this->set_username(Message::read_length_prepended_string(_marshalled_message));
        break;
    case ImageChunk:
        this->set_image_id(Message::read_length_prepended_string(_marshalled_message));
        this->set_image_chunk_index(Message::deserialize_int(_marshalled_message));
        this->set_image_num_chunks(Message::deserialize_int(_marshalled_message));
        this->set_image_chunk_content(Message::read_length_prepended_string(_marshalled_message));
        break;
    case Error:
        this->set_error_message(Message::read_length_prepended_string(_marshalled_message));
        break;
    default: throw std::runtime_error("RPCId not supported for marshalling!");
    }
}
string Message::marshal () const
{
    string ans = Message::serialize_int((int) this->rpc_id);
    switch(this->rpc_id)
    {
    case SignUpRequest:
    case SignInRequest:
        ans = ans + Message::prepend_length(this->get_username()) + Message::prepend_length(this->get_password());
        break;
    case SignUpConfirmation:
    case SignInConfirmation:
        break;
    case SignOutRequest:
        ans = ans + Message::prepend_length(this->get_username());
        break;
    case Error:
        ans = ans + Message::prepend_length(this->get_error_message());
        break;
    case ImageChunk:
        ans = ans +
                Message::prepend_length(this->get_image_id()) +
                Message::serialize_int(this->get_image_chunk_index()) +
                Message::serialize_int(this->get_image_num_chunks()) +
                Message::prepend_length(this->get_image_chunk_content());
        break;
    default:
        throw std::runtime_error("RPCId not supported for marshalling!");
    }
    return ans;
}


// Setters
void Message::set_username(const string & _username){
    this->username = _username;
}
void Message::set_password(const string & _password){
    this->password = _password;
}
void Message::set_error_message(const string & _error_message){
    this->error_message = _error_message;
}
void Message::set_image_id(const string &_image_id){
    this->image_id = _image_id;
}
void Message::set_image_chunk_content(const string & _image_partition_content){
    this->image_chunk_content = _image_partition_content;
}
void Message::set_image_chunk_index(const int32_t _image_partition_index){
    this->image_chunk_index = _image_partition_index;
}
void Message::set_image_num_chunks(const int32_t _image_num_chunks)
{
    this->image_num_chunks = _image_num_chunks;
}

// Getters
RPCId Message::get_rpc_id() const{
    return this->rpc_id;
}
string Message::get_username() const{
    return this->username;
}
string Message::get_password() const{
    return this->password;
}
string Message::get_error_message() const{
    return this->error_message;
}
string Message::get_image_id() const{
    return this->image_id;
}
string Message::get_image_chunk_content() const{
    return this->image_chunk_content;
}
int32_t Message::get_image_chunk_index() const{
    return this->image_chunk_index;
}
int32_t Message::get_image_num_chunks() const{
    return this->image_num_chunks;
}

// Serialization auxiliary functions!
string Message::serialize_int(int32_t i)
{
    string ans = "";
    i = htonl(i);
    for (int byte = 0; byte < 4; ++byte)
    {
        char c = (i >> (byte * 8)) & 255;
        ans = ans + string(1, c);
    }
    return ans;
}
int32_t Message::deserialize_int(const char * & serialized_int)
{
    int32_t x = 0;
    for (int byte = 0; byte < 4; ++byte, ++serialized_int)
    {
        int32_t c = *serialized_int;
        x |= (c << (byte * 8));
    }
    return ntohl(x);
}
string Message::prepend_length(const string & _str, const bool _strict)
{
    if (_strict && _str.empty())
    {
        throw std::runtime_error("Attempting to serialize an empty string!");
    }
    return Message::serialize_int(_str.length()) + _str;
}
string Message::read_length_prepended_string(const char * & s)
{
    int32_t length = Message::deserialize_int(s);
    if (length > Message::MAX_STR_LEN || length <= 0)
    {
        throw std::runtime_error(
                    "Error parsing received message: Invalid string length: " + std::to_string(length));
    }
    string ans = "";
    while(length--)
        ans += string(1, *s++);
    return ans;
}
