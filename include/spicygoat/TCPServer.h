//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_TCPSERVER_H
#define SPICYGOAT_TCPSERVER_H

#include <list>

#ifdef __linux__
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#endif

#ifdef _WIN64
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#include <spdlog/spdlog.h>
#include <spicygoat/TCPConnection.h>

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

   private:
    bool running = true;

    std::shared_ptr<spdlog::logger> logger;

    unsigned long long sock;
    pollfd fds[10];

    std::list<std::shared_ptr<TCPConnection>> connections;

    std::unique_ptr<std::thread> keepAliveThread;
};

#endif  // SPICYGOAT_TCPSERVER_H
