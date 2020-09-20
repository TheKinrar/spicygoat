//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_TCPSERVER_H
#define SPICYGOAT_TCPSERVER_H

#include "TCPConnection.h"

#include <libnet.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>

class TCPServer {
public:
    TCPServer();

    ~TCPServer();

    TCPServer(const TCPServer&) = delete;

    void operator=(const TCPServer&) = delete;

    static TCPServer& get();

    void accept();

    void keepAliveTask();

    bool isRunning() const;

    void stop();

    void removeConnection(TCPConnection*);

private:
    bool running = true;

    int sock;
    pollfd fds[10];

    std::forward_list<TCPConnection*> connections;
};


#endif//SPICYGOAT_TCPSERVER_H
