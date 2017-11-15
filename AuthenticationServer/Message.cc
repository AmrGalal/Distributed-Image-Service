#include <string>
#include <vector>
#include <exception>
#include <arpa/inet.h>
#include<bits/stdc++.h>
#include "Message.h"

Message::Message (RPCId _rpc_id){
    this->rpc_id = _rpc_id;
}
Message::Message (const char * _marshalled_message){
    this->rpc_id = (RPCId) Message::deserialize_int(_marshalled_message);
    _marshalled_message += 4;
    switch(this->rpc_id)
    {
    case SignUpRequest:
    case SignInRequest:
        this->username = read_length_prepended_string(_marshalled_message);
        _marshalled_message += (4 + this->username.length());
        this->password = read_length_prepended_string(_marshalled_message);
        _marshalled_message += (4 + this->password.length());
        break;
    case SignUpConfirmation:
    case SignInConfirmation:
        this->username = read_length_prepended_string(_marshalled_message);
        _marshalled_message += (4 + this->username.length());
        break;
    case Error:
        this->error_message = read_length_prepended_string(_marshalled_message);
        _marshalled_message += (4 + this->error_message.length());
        break;
    default: throw "RPCId not supported for marshalling!";
    }
}
string Message::marshal () const{
    string ans = Message::serialize_int((int) this->rpc_id);
    switch(this->rpc_id)
    {
    case SignUpRequest:
    case SignInRequest:
        ans = ans + Message::prepend_length(this->username) + Message::prepend_length(this->password); break;
    case SignUpConfirmation:
    case SignInConfirmation:
        ans = ans + Message::prepend_length(this->username); break;
    case Error:
        ans = ans + Message::prepend_length(this->error_message); break;
    default: throw "RPCId not supported for marshalling!";
    }
    return ans;
}
Message::~Message (){}
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
int32_t Message::deserialize_int(const char * serialized_int)
{
    int32_t x = 0;
    for (int byte = 0; byte < 4; ++byte)
    {
        int32_t c = serialized_int[byte];
        x |= (c << (byte * 8));
    }
    return ntohl(x);
}
string Message::prepend_length(const string & s)
{
    return Message::serialize_int(s.length()) + s;
}
string Message::read_length_prepended_string(const char * s)
{
    const int length = Message::deserialize_int(s);
    string ans = "";
    for (int i = 0; i < length; ++i)
        ans += string(1, s[4 + i]);
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
void Message::setImagePartitionIndex(const int _image_partition_index){
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
int Message::getImagePartitionIndex() const{
    return this->image_partition_index;
}
