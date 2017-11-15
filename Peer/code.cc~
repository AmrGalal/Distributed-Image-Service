#include <iostream>

#include "Message.h"

using namespace std;

int main()
{
  Message m(SignUpRequest);
  m.setUsername("bishoyboshra");
  m.setPassword("password");
  string s = m.marshal();
  Message reconstructed(s.c_str());
  cout << reconstructed.getRPCId() << endl;
  cout << reconstructed.getUsername() << endl;
  cout << reconstructed.getPassword() << endl;
}
