#include <string>
#include <array>

#include "user.h"

User::User(const std::string & _username,
           const std::string & _password,
           const std::string & _ip,
           const int & _port,
           const bool _is_signed_in)
{
    this->username = _username;
    this->password = _password;
    this->ip = _ip;
    this->port = _port;
    this->is_signed_in = _is_signed_in;
}
User::User(const std::string & _serialized_user)
{
    std::array<std::string, 5> info;
    int cursor_start = 0, cursor_end = 0;
    for (int i = 0; i < 5; ++i)
    {
        cursor_end = _serialized_user.find('\t', cursor_start);
        info[i] = _serialized_user.substr(cursor_start, cursor_end - cursor_start);
        cursor_start = cursor_end + 1;
    }
    this->username = info[0];
    this->password = info[1];
    this->ip = info[2];
    this->port = atoi(info[3].c_str());
    this->is_signed_in = (bool) atoi(info[4].c_str());
}

// Serialization
std::string User::serialize()
{
    const std::array<std::string, 5> info = {
        this->username,
        this->password,
        this->ip,
        std::to_string(this->port),
        std::to_string(this->is_signed_in)
    };
    std::string ans = "";
    for (auto field : info)
    {
        if (ans != "")
            ans += "\t";
        ans += field;
    }
    return ans;
}
// Sign in and sign out.
void User::sign_in()
{
    this->is_signed_in = true;
}
void User::sign_out()
{
    this->is_signed_in = false;
}

// Setters and Getters!
std::string User::getUsername() const
{
    return this->username;
}
bool User::isCorrectPassword(const std::string & _password) const
{
    return this->password == _password;
}
std::string User::getIP() const
{
    return this->ip;
}
int User::getPort() const
{
    return this->port;
}
bool User::isSignedIn() const
{
    return this->is_signed_in;
}
bool User::operator < (const User & _other) const
{
    return this->getUsername() < _other.getUsername();
}
