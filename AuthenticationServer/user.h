#include <string>

#ifndef USER_H
#define USER_H


class User{
public:
    User(const std::string & _username, const std::string & _password, const std::string & _ip, const int & _port, const bool _is_signed_in = false);
    User(const std::string & _serialized_user);
    void sign_in();
    void sign_out();
    // Getters!
    std::string get_username() const;
    bool is_correct_password(const std::string & _password) const;
    std::string get_ip() const;
    int get_port() const;
    bool is_signed_in() const;
    // Comparator!
    std::string serialize();
private:
    std::string username;
    std::string password;
    std::string ip;
    int port;
    bool signed_in_flag = false;
};

#endif // USER_H
