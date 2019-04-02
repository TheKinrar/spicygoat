//
// Created by thekinrar on 30/03/19.
//

#include "TCPServer.h"

#include <iostream>

TCPServer::TCPServer() {
    sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sin;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(25566);

    bind(sock, (sockaddr*) &sin, sizeof(sin));

    std::cerr << strerror(errno) << std::endl;

    listen(sock, 5);

    std::cerr << strerror(errno) << std::endl;
}

TCPServer::~TCPServer() {
    close(sock);
}

void TCPServer::accept() {
    sockaddr_in csin;
    socklen_t csinlen = sizeof(csin);
    int csock = ::accept(sock, (sockaddr*) &csin, &csinlen);

    TCPConnection connection(csock, csin);
    connection.task();
}
