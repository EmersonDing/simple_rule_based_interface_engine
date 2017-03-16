#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


class TCPSocket // TCP Socket Class
{
private:
    int sock;
    struct sockaddr_in serverAddr;
public:
    // A constructor that performs all the client connection initialization to a server socket
    TCPSocket (char * _address, int port, int readBufferSize=65536, int writeBufferSize=65536);
    // Ths constructor is used when the socket is already created and established prior to object instantiation
    TCPSocket (int _sock, int readBufferSize=65536, int writeBufferSize=65536);
    int readFromSocket (char * buffer, int maxBytes );  // Blocking read data from socket with an upperbound size
    // Write data to a socket with a specified size.
    int writeToSocket (const char * buffer, long maxBytes );
    // Set the status of the socket peer as disconnected
    ~TCPSocket ( ); // Destructor: shutdown the target socket and deallocate all its resources
};

#endif // TCPSOCKET_H

