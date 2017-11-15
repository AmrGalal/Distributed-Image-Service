#include <string>
#include <iostream>
#include "Message.h"

int main()
{
  Message m(SignUpRequest);
  m.setUsername("amr");
  m.setPassword("pass");
  std::string s = m.marshal();
  cout << "length: " << s.length() << endl;
  Message r(s.c_str());
  cout << r.getRPCId() << endl;
  cout << r.getUsername() << endl;
  cout << r.getPassword() << endl;
  return 0;
}

