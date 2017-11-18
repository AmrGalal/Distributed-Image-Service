#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdexcept>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Socket.h"

Socket::Socket(const int _local_port) {
	if ((this->s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
        throw std::runtime_error("Socket initialization failed!");
	}
	this->address.sin_family = AF_INET;
	this->address.sin_port = htons (_local_port);
	this->address.sin_addr.s_addr = htonl (INADDR_ANY);
	if (bind (s, (const sockaddr*) &(this->address), sizeof (struct sockaddr_in)) != 0)
	{
        throw std::runtime_error("Socket binding failed!");
		close (s);
	}
}

void Socket::makeDestSA (struct sockaddr_in *sa, const char *hostname, const int port)
{
	struct hostent *host;
	sa->sin_family = AF_INET;
	if ((host = gethostbyname (hostname)) == NULL)
	{
        throw std::runtime_error("Invalid host name!");
	}
	sa->sin_addr = *(struct in_addr *) (host->h_addr);
	sa->sin_port = htons (port);
}

void Socket::send (const Message & message, const char *hostname, const int port)
{
	int n;
	struct sockaddr_in yourSocketAddress;
	makeDestSA (&yourSocketAddress, hostname, port);
    string marshalled_message = message.marshal();
	if ((n =
        sendto (s, (void*) marshalled_message.c_str(), marshalled_message.length(), 0,
			(const sockaddr*) &yourSocketAddress, sizeof (struct sockaddr_in))) < 0)
        {
        throw std::runtime_error("Socket send failed!");
    }
}

void Socket::receive (Message & received_message, struct sockaddr_in &aSocketAddress)
{
	int aLength, n;

	aLength = sizeof (aSocketAddress);
	aSocketAddress.sin_family = AF_INET;
	if ((n = recvfrom (s, buffer, BUFFER_SIZE, 0, (sockaddr*) &aSocketAddress, (socklen_t*) &aLength)) < 0)
	{
        throw std::runtime_error("Socket receive failed!");
	}
    received_message = Message(buffer);
}

Socket::~Socket()
{
	close (this->s);
}
