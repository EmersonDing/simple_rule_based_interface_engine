#ifndef TCPSERVERSOCKET_H
#define TCPSERVERSOCKET_H

#include "TCPSocket.h"


class TCPServerSocket // TCP Server Socket
{
private:
    int sock;   // Socket Handler
    struct sockaddr_in serverAddr;  // Server Socket Address Structure
    struct sockaddr_in clientAddr;  // Client Socket Address Structure
    socklen_t sin_size = sizeof(struct sockaddr_in);
public:
    // Constructor
    TCPServerSocket (int port);
    //bool initializeSocket (); // Initailize server socket
    // Wait for a client connection and return a TCPSocket object that represents the client
    TCPSocket * getConnection (int readBufferSize=10*1024*1024,int writeBufferSize=10*1024*1024);
    ~TCPServerSocket ( ); // Destructor
};

#endif // TCPSERVERSOCKET_H
