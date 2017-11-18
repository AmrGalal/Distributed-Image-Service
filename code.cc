#include <fstream>
#include <iostream>
#include <vector>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>

#include "Socket.h"
#include "Message.h"

inline std::string read_binary_file(const std::string file_name)
{
  std::ifstream input_file;
  input_file.open(file_name.c_str(), std::ios::in|std::ios::binary|std::ios::ate);
  std::ifstream::pos_type size = input_file.tellg();
  input_file.seekg(0, std::ios::beg);
  char * data = new char[size];
  input_file.read(data, size);
  std::string ans;
  for (int i = 0; i < size; ++i) ans += std::string(1, data[i]);
  return ans;
}

int main(int argc, char **argv)
{
  Socket socket(atoi(argv[1]));
  std::ofstream f;
  f.open(argv[3]);
  pid_t pid = fork();
  if (pid) {
    Message m(SignUpConfirmation);
    sockaddr_in address;
    socket.receive(m, address);
    f << m.getErrorMessage();
    f.close();
  } else {
    std::vector<std::string> v = {"hello", "world"};
    for (const auto & s : v) {
      Message m(Error);
      m.setErrorMessage(s);
      socket.send(m, "127.0.0.1", atoi(argv[2]));
    }
  }
  return 0;
}

