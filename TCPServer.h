//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_TCPSERVER_H
#define SPICYGOAT_TCPSERVER_H

#include "TCPConnection.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <libnet.h>

class TCPServer {
public:
    TCPServer();
    ~TCPServer();

    void accept();

private:
    int sock;
};


#endif //SPICYGOAT_TCPSERVER_H
