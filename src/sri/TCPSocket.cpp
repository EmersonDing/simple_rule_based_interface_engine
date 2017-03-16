#include "TCPSocket.h"
#include <iostream>

TCPSocket::TCPSocket(int _sock, int readBufferSize, int writeBufferSize) {
    sock = _sock;
}

TCPSocket::TCPSocket(char* _address, int port, int readBufferSize, int writeBufferSize) {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error Creating Socket");
        throw(0);
    }
    memset((char *) &serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    struct hostent *server = gethostbyname(_address);
    if (server == NULL) throw(1);
    memcpy((char *) &serverAddr.sin_addr.s_addr, (char *) server->h_addr, server->h_length);
    //memcpy(&(serverAddr.sin_zero), 0, 8);
    
    if (connect(sock, (sockaddr *) &serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error Creating Socket");
        throw(2);
    }
    std::cout << "Socket opened" << "\n";
}

TCPSocket::~TCPSocket() {
    close(sock);
    std::cout << "Socket closed" << "\n";
}

int TCPSocket::writeToSocket(const char* buffer, long maxBytes) {
    if (buffer == NULL) return -1;
    return send(sock, buffer, maxBytes, 0);
}

int TCPSocket::readFromSocket(char* buffer, int maxBytes) {
    memset(buffer, 0, maxBytes/8);
    return recv(sock, buffer, maxBytes, 0);
}