//
// Created by thekinrar on 30/03/19.
//

#include "TCPServer.h"

#include <arpa/inet.h>
#include <iostream>
#include <memory>
#include <sys/ioctl.h>
#include <thread>

#include "config/Config.h"
#include "network/listeners/HandshakeListener.h"

TCPServer::TCPServer() {
#ifdef _WIN64
    WSAData wsaData = {};
    if(WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
    }
#endif

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

#ifdef __linux__
    ioctl(sock, FIONBIO);
    int enable = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
    setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int));
#endif

#ifdef _WIN64
    u_long blockMode = 0;
    char reuseAddrOpt = 1;
    ioctlsocket(sock, FIONBIO, &blockMode);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseAddrOpt, sizeof(reuseAddrOpt));
#endif

    sockaddr_in sin{};
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("0.0.0.0");
    sin.sin_port = htons(Config::get().port);

    errno = 0;
    if(bind(sock, (sockaddr *)&sin, sizeof(sin))) {
#ifdef __linux__
        std::cerr << "bind failed: " << strerror(errno) << std::endl;
#endif
#ifdef _WIN64
        std::cerr << "bind failed: " << WSAGetLastError() << std::endl;
#endif
        exit(1);
    }

    errno = 0;
    listen(sock, 5);

    if(errno) {
        std::cerr << "listen failed: " << strerror(errno) << std::endl;
        exit(1);
    }

    memset(fds, 0, sizeof(fds));

    fds[0].fd = sock;
    fds[0].events = POLLIN;

    keepAliveThread = std::make_unique<std::thread>(&TCPServer::keepAliveTask, this);

    std::cout << "Ready!" << std::endl;
}

TCPServer::~TCPServer() {
    std::cout << "TCP server stopped" << std::endl;
}

void TCPServer::accept() {
    while(running) {
#ifdef __linux__
        int ret = poll(fds, 1, 100);
#endif

#ifdef _WIN64
        int ret = WSAPoll(fds, 1, 100);
#endif

        if(ret > 0) {
            std::cout << "accept" << std::endl;

            sockaddr_in csin;
            socklen_t csinlen = sizeof(csin);
            int csock = ::accept(sock, (sockaddr *)&csin, &csinlen);

            auto conn = std::make_shared<TCPConnection>(csock, csin);
            conn->setListener(std::make_unique<HandshakeListener>(conn));
            connections.push_front(conn);
        }
    }

    std::cout << "TCP server stopping" << std::endl;
    for(auto conn : connections) {
        conn->disconnect();
    }
    closesocket(sock);
}

void TCPServer::keepAliveTask() {
    while(running) {
        int64_t millis =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                .count();

        auto it = connections.begin();
        while(it != connections.end()) {
            auto &connection = *it;
            if(!connection->alive) {
                it = connections.erase(it);
            } else {
                if(connection->getState() == ProtocolState::PLAY) {
                    connection->keepAlive(millis);
                }

                ++it;
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

bool TCPServer::isRunning() const {
    return running;
}

void TCPServer::stop() {
    running = false;
}

TCPServer &TCPServer::get() {
    static TCPServer server;
    return server;
}
