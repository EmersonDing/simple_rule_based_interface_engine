#include "TCPServerSocket.h"
#include <iostream>

TCPServerSocket::TCPServerSocket(int port) {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error Creating Socket");
        throw(0);
    }
    int sock_opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *) &sock_opt, sizeof(sock_opt));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    //memset(&(serverAddr.sin_zero), 0, 1);
    if (bind(sock, (struct sockaddr *) &serverAddr, sizeof(struct sockaddr)) == -1) {
        perror("Error Binding Socket");
        throw(1);
    }
    if (listen(sock, 10) == -1) {
        perror("Error Listening on Socket");
        throw(2);
    }
    std::cout << "Server socket opened" << "\n";
}

TCPSocket * TCPServerSocket::getConnection(int readBufferSize, int writeBufferSize) {
    int newsock = accept(sock, (struct sockaddr *) &clientAddr, &sin_size);
    if (newsock < 1) return NULL;
    return new TCPSocket(newsock, readBufferSize, writeBufferSize);
}

TCPServerSocket::~TCPServerSocket() {
    close(sock);
    std::cout << "Server socked closed" << "\n";
}