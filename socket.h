#ifndef Socket_H
#define Socket_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <netinet/in.h>
#include <stdio.h>
#include "message.h"

class Socket
{
	const static int BUFFER_SIZE = 1 << 13;
private:
	void print(const char * message);
	void makeDestSA (struct sockaddr_in *sa, const char *hostname, const int port);

	int s;
	struct sockaddr_in address;
	char buffer[BUFFER_SIZE];
public:
	Socket(int _local_port);
	void send (const Message & message, const char *hostname, const int port);
    pair<Message, struct sockaddr_in> receive();
	~Socket();
};
#endif
