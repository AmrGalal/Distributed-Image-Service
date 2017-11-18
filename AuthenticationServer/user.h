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
    std::string getUsername() const;
    bool isCorrectPassword(const std::string & _password) const;
    std::string getIP() const;
    int getPort() const;
    bool isSignedIn() const;
    // Comparator!
    bool operator < (const User & _other) const;
    std::string serialize();
private:
    std::string username;
    std::string password;
    std::string ip;
    int port;
    bool is_signed_in = false;
};

#endif // USER_H
