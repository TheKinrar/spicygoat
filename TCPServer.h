//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_TCPSERVER_H
#define SPICYGOAT_TCPSERVER_H

#include "TCPConnection.h"

#include <boost/asio.hpp>

class TCPServer {
public:
    TCPServer();

    ~TCPServer();

    TCPServer(const TCPServer&) = delete;

    void operator=(const TCPServer&) = delete;

    static TCPServer& get();

    void accept();
    void handleAccept(const boost::system::error_code& ec, boost::asio::ip::tcp::socket&& sock);

    void keepAliveTask();

    bool isRunning() const;

    void stop();

    void removeConnection(TCPConnection*);

private:
    bool running = true;

    boost::asio::io_service service;
    boost::asio::ip::tcp::acceptor acceptor;

    std::forward_list<TCPConnection*> connections;
};


#endif//SPICYGOAT_TCPSERVER_H
