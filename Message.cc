#include <string>
#include <vector>
#include <stdexcept>

#include <arpa/inet.h>

#include "Message.h"

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
        this->setUsername(read_length_prepended_string(_marshalled_message));
        this->setPassword(read_length_prepended_string(_marshalled_message));
        break;
    case SignUpConfirmation:
    case SignInConfirmation:
        break;
    case SignOutRequest:
        this->setUsername(read_length_prepended_string(_marshalled_message));
        break;
    case Error:
        this->setErrorMessage(read_length_prepended_string(_marshalled_message));
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
        ans = ans + Message::prepend_length(this->getUsername()) + Message::prepend_length(this->getPassword());
        break;
    case SignUpConfirmation:
    case SignInConfirmation:
        break;
    case SignOutRequest:
        ans = ans + Message::prepend_length(this->getUsername());
        break;
    case Error:
        ans = ans + Message::prepend_length(this->getErrorMessage());
        break;
    default:
        throw std::runtime_error("RPCId not supported for marshalling!");
    }
    return ans;
}

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


// Setters
void Message::setUsername(const string & _username){
    this->username = _username;
}
void Message::setPassword(const string & _password){
    this->password = _password;
}
void Message::setErrorMessage(const string & _error_message){
    this->error_message = _error_message;
}
void Message::setImagePartitionContent(const string & _image_partition_content){
    this->image_partition_content = _image_partition_content;
}
void Message::setImagePartitionIndex(const int32_t _image_partition_index){
    this->image_partition_index = _image_partition_index;
}

// Getters
RPCId Message::getRPCId() const{
    return this->rpc_id;
}
string Message::getUsername() const{
    return this->username;
}
string Message::getPassword() const{
    return this->password;
}
string Message::getErrorMessage() const{
    return this->error_message;
}
string Message::getImagePartitionContent() const{
    return this->image_partition_content;
}
int32_t Message::getImagePartitionIndex() const{
    return this->image_partition_index;
}
