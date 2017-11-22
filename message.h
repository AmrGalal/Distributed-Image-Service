#ifndef MESSAGE_H
#define MESSAGE_H
#include <string.h>
#include <stdexcept>
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
    Error,
    oneChunkRequested,

    // Image
    ImageChunk
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

    string image_id;
    string image_chunk_content;
    int32_t image_chunk_index;
    int32_t image_num_chunks;
    // Serialization!
    static string serialize_int(const int32_t i);
    static int32_t deserialize_int(const char * &serialized_int);
    static string prepend_length(const string & _str, const bool _strict = true);
    static string read_length_prepended_string(const char * & s);
    struct ImageChunkIndexCmp
    {
      inline bool operator ()(const Message & a, const Message & b)
      {
          if (a.get_rpc_id() != ImageChunk || b.get_rpc_id() != ImageChunk)
          {
              throw std::runtime_error("Can not compare two non-image-chunk messages!");
          }
          return a.get_image_chunk_index() < b.get_image_chunk_index();
      }
    };
public:
    // Message();
    Message (RPCId _rpc_id);
    Message (const char * _marshalled_message);
    Message(){}
    string marshal () const;
    ~Message ();
    // Setters
    void set_username(const string & _username);
    void set_password(const string & _password);
    void set_error_message(const string & _error_message);
    void set_image_id(const string & _image_id);
    void set_image_chunk_content(const string & _image_partition_content);
    void set_image_chunk_index(const int32_t _image_partition_index);
    void set_image_num_chunks(const int32_t _image_num_chunks);
    // Getters
    RPCId get_rpc_id() const;
    string get_username() const;
    string get_password() const;
    string get_error_message() const;
    string get_image_id() const;
    string get_image_chunk_content() const;
    int32_t get_image_chunk_index() const;
    int32_t get_image_num_chunks() const;
    // Comparators
    static ImageChunkIndexCmp image_chunk_index_cmp;
};
#endif // MESSAGE_H
