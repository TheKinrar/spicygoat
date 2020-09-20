//
// Created by thekinrar on 30/03/19.
//

#include "TCPServer.h"
#include "network/listeners/HandshakeListener.h"

#include <iostream>
#include <memory>
#include <thread>

TCPServer::TCPServer() : service{}, acceptor{service, {boost::asio::ip::tcp::v4(), 25565}} {
    acceptor.listen();

    new std::thread(&TCPServer::keepAliveTask, this);
}

TCPServer::~TCPServer() {
    std::cout << "TCP server stopped" << std::endl;
}

void TCPServer::accept() {
    try {
        acceptor.async_accept([this](auto ec, auto&& sock) {
            handleAccept(ec, std::forward<decltype(sock)>(sock));
        });
        while (running) {
            service.poll_one();
        }
    } catch (const std::exception& exception) {
        std::cerr << exception.what();
    }

    std::cout << "TCP server stopping" << std::endl;
    for (auto conn : connections) {
        conn->disconnect();
    }
    acceptor.close();
}

void TCPServer::keepAliveTask() {
    while (running) {
        int64_t millis = std::chrono::duration_cast<std::chrono::milliseconds>(
                                 std::chrono::system_clock::now().time_since_epoch())
                                 .count();

        for (auto connection : connections) {
            if (connection->getState() == ProtocolState::PLAY) {
                connection->keepAlive(millis);
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

void TCPServer::removeConnection(TCPConnection* conn) {
    connections.remove(conn);
}

TCPServer& TCPServer::get() {
    static TCPServer server;
    return server;
}
void TCPServer::handleAccept(const boost::system::error_code& ec, boost::asio::ip::tcp::socket&& sock) {
    auto conn = new TCPConnection(std::forward<boost::asio::ip::tcp::socket>(sock));
    conn->setListener(std::make_unique<HandshakeListener>(*conn));
    connections.push_front(conn);

    acceptor.async_accept([this](auto ec, auto&& sock) {
        handleAccept(ec, std::forward<decltype(sock)>(sock));
    });
}
