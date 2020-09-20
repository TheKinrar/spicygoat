//
// Created by thekinrar on 30/03/19.
//

#include <iostream>

#include "Server.h"
#include "TCPConnection.h"
#include "TCPServer.h"
#include "entities/EntityPlayer.h"
#include "protocol.h"

TCPConnection::TCPConnection(boost::asio::ip::tcp::socket sock) : sock(std::move(sock)) {
    thread = std::thread(&TCPConnection::task, this);
}

void TCPConnection::sendPacket(Packet* packet) {
    m_send.lock();

    int i = packet->getId();
    if (i == 0x04 || i == 0x27 || i == 0x28 || i == 0x29 || i == 0x32 || i == 0x36 || i == 0x56) {
        std::cout << getName() << " <= " << packet->toString() << std::endl;
    }

    std::vector<std::byte> data = packet->bytes();

    std::vector<std::byte> bytes;
    PacketData::writeVarInt(data.size(), bytes);
    bytes.insert(bytes.end(), data.begin(), data.end());

    boost::asio::write(sock, boost::asio::buffer(bytes));
    m_send.unlock();
}

void TCPConnection::task() {
    std::cout << getName() << " connected" << std::endl;

    try {
        while (TCPServer::get().isRunning()) {
            std::vector<char> buffer(readVarInt());
            boost::asio::read(sock, boost::asio::buffer(buffer));

            PacketData packetData(buffer.data(), buffer.size());
            Packet* packet = Packets::parse(&packetData, state);

            if (packet) {
                //                std::cout << getName() << " => " << packet->toString() << std::endl;

                if (listener) listener->handle(*static_cast<ServerBoundPacket*>(packet));
            }
        }
    } catch (std::exception& e) {
        sock.close();
        std::cout << getName() << " disconnected: " << e.what() << std::endl;
        TCPServer::get().removeConnection(this);

        if (player) {
            Server::get()->removePlayer(*player);
        }
    }
}

int TCPConnection::readVarInt() {
    int bytes = 0;
    int result = 0;
    char current;

    do {
        boost::asio::read(sock, boost::asio::buffer(&current, sizeof(current)));

        int value = (current & 0b01111111);
        result |= (value << (7 * bytes));

        bytes++;

        if (bytes > 5) {
            throw std::runtime_error("Protocol error: invalid VarInt");
        }

    } while ((current & 0b10000000) != 0);

    return result;
}

void TCPConnection::setState(ProtocolState newState) {
    state = newState;
}

ProtocolState TCPConnection::getState() const {
    return state;
}

std::string TCPConnection::getName() {
    auto remoteEndpoint = sock.remote_endpoint();
    return remoteEndpoint.address().to_string() + ":" + std::to_string(remoteEndpoint.port()) + "/" +
           std::to_string(state);
}

EntityPlayer* TCPConnection::getPlayer() {
    return player;
}

void TCPConnection::setPlayer(EntityPlayer* newPlayer) {
    this->player = newPlayer;
}

void TCPConnection::keepAlive(int64_t millis) {
    if (keepAliveOk) {
        if (millis - latestKeepAlive > 10000) {
            m_keepAlive.lock();

            latestKeepAlive = millis;
            keepAliveOk = false;
            sendPacket(new PacketKeepAliveCB(millis));

            m_keepAlive.unlock();
        }
    } else {
        if (millis - latestKeepAlive > 30000) {
            sock.close();// TODO proper timeout
        }
    }
}

void TCPConnection::confirmKeepAlive(int64_t id) {
    if (id != latestKeepAlive)
        throw std::runtime_error("Protocol error: invalid keep alive ID");

    if (keepAliveOk)
        throw std::runtime_error("Protocol error: keep alive already confirmed");

    m_keepAlive.lock();
    keepAliveOk = true;
    m_keepAlive.unlock();
}

void TCPConnection::setListener(std::unique_ptr<PacketListener> newListener) {
    listener = std::move(newListener);
}

const PacketListener& TCPConnection::getListener() const {
    return *listener;
}

void TCPConnection::disconnect() {
    sock.close();
}
