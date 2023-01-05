//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_TCPSERVER_H
#define SPICYGOAT_TCPSERVER_H

#include "TCPConnection.h"

#ifdef __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#include <libnet.h>
#include <poll.h>
#endif

#ifdef _WIN64
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

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

    void removeConnection(const TCPConnection&);

private:
    bool running = true;

    unsigned long long sock;
    pollfd fds[10];

    std::forward_list<std::shared_ptr<TCPConnection>> connections;

    std::unique_ptr<std::thread> keepAliveThread;
};


#endif //SPICYGOAT_TCPSERVER_H
