#ifndef MESSAGE_H
#define MESSAGE_H
#include <string.h>
#include <cstdint>
#include <string>

using namespace std;
// enum MessageType { Request, Reply };
enum RPCId : int32_t {
    // Authentication
    SignUpRequest,
    SignUpConfirmation,
    SignInRequest,
    SignInConfirmation,
    SignOutRequest,
    // Generic Error!
    Error
};

class Message
{
private:
    // Maximum string length!
    const static int32_t MAX_STR_LEN = 1 << 13;
    // Fields related to the communication protocol.
    // Those fields have very special handling, and do not simply have setters and getters.
    RPCId rpc_id;
    // Fields related to message content.
    string username;
    string password;
    string error_message;
    string image_partition_content;
    int32_t image_partition_index;
    static string serialize_int(const int32_t i);
    static int32_t deserialize_int(const char * &serialized_int);
    static string prepend_length(const string & _str, const bool _strict = true);
    static string read_length_prepended_string(const char * & s);
public:
    // Message();
    Message (RPCId _rpc_id);
    Message (const char * _marshalled_message);
    string marshal () const;
    ~Message ();
    // Setters
    void setUsername(const string & _username);
    void setPassword(const string & _password);
    void setErrorMessage(const string & _error_message);
    void setImagePartitionContent(const string & _image_partition_content);
    void setImagePartitionIndex(const int32_t _image_partition_index);
    // Getters
    RPCId getRPCId() const;
    string getUsername() const;
    string getPassword() const;
    string getErrorMessage() const;
    string getImagePartitionContent() const;
    int32_t getImagePartitionIndex() const;
};
#endif // MESSAGE_H
