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

    void keepAliveTask();

    bool isRunning() const;
    void stop();

private:
    bool running = true;

    int sock;

    std::vector<TCPConnection*> connections;
};


#endif //SPICYGOAT_TCPSERVER_H
