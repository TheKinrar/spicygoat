//
// Created by thekinrar on 30/03/19.
//

#include "TCPConnection.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <sstream>

#include "Server.h"
#include "TCPServer.h"
#include "entities/types/EntityPlayer.h"
#include "protocol.h"

TCPConnection::TCPConnection(int sock, sockaddr_in addr) : sock(sock), addr(addr) {
    thread = std::make_unique<std::thread>(&TCPConnection::task, this);
}

void TCPConnection::sendPacket(const Packet &packet) {
    m_send.lock();

    //    int i = packet->getId();
    //    if(i == Packets::...) {
    //        std::cout << getName() << " <= " << packet->toString() << std::endl;
    //    }

    std::vector<std::byte> data = packet.bytes();

    std::vector<std::byte> bytes;
    PacketData::writeVarInt(data.size(), bytes);
    bytes.insert(bytes.end(), data.begin(), data.end());

    send(sock, (char *)bytes.data(), bytes.size(), 0);
    m_send.unlock();
}

void TCPConnection::task() {
    std::cout << getName() << " connected" << std::endl;

    try {
        while(TCPServer::get().isRunning()) {
            int length = readVarInt();

            auto data = std::make_unique<char[]>(length);
            recv(sock, data.get(), length, 0);

            PacketData packetData(std::move(data), length);
            auto packet = Packets::parse(packetData, state);

            if(packet && packetData.remaining()) {
                std::stringstream ss;
                ss << "Protocol error: extra data (" << std::to_string(packetData.remaining())
                   << " B) left after parsing " << packet->toString();
                throw std::runtime_error(ss.str());
            }

            if(packet) {
                //                std::cout << getName() << " => " << packet->toString() << std::endl;

                if(listener) listener->handle(dynamic_cast<const ServerBoundPacket &>(*packet));
            }
        }
    } catch(std::exception &e) {
        closesocket(sock);
        std::cout << getName() << " disconnected: " << e.what() << std::endl;

        if(player) {
            Server::get().removePlayer(*player);
        }
    }

    alive = false;
}

int TCPConnection::readVarInt() {
    int bytes = 0;
    int result = 0;
    char current;

    do {
        int size;
        if((size = recv(sock, &current, sizeof(current), 0)) < 1) {
            throw std::runtime_error(std::string("Network error: ") + strerror(errno));
        }

        int value = (current & 0b01111111);
        result |= (value << (7 * bytes));

        bytes++;

        if(bytes > 5) {
            throw std::runtime_error("Protocol error: invalid VarInt");
        }

    } while((current & 0b10000000) != 0);

    return result;
}

void TCPConnection::setState(ProtocolState newState) {
    state = newState;
}

ProtocolState TCPConnection::getState() const {
    return state;
}

std::string TCPConnection::getName() {
    return std::string(inet_ntoa(addr.sin_addr)) + ":" + std::to_string(htons(addr.sin_port)) + "/" +
           std::to_string(state);
}

void TCPConnection::keepAlive(int64_t millis) {
    if(keepAliveOk) {
        if(millis - latestKeepAlive > 10000) {
            m_keepAlive.lock();

            latestKeepAlive = millis;
            keepAliveOk = false;
            sendPacket(PacketKeepAliveCB(millis));

            m_keepAlive.unlock();
        }
    } else {
        if(millis - latestKeepAlive > 30000) {
            closesocket(sock);  // TODO proper timeout
        }
    }
}

void TCPConnection::confirmKeepAlive(int64_t id) {
    if(id != latestKeepAlive) throw std::runtime_error("Protocol error: invalid keep alive ID");

    if(keepAliveOk) throw std::runtime_error("Protocol error: keep alive already confirmed");

    m_keepAlive.lock();
    keepAliveOk = true;
    m_keepAlive.unlock();
}

void TCPConnection::setListener(std::unique_ptr<PacketListener> newListener) {
    listener = std::move(newListener);
}

const PacketListener &TCPConnection::getListener() const {
    return *listener;
}

void TCPConnection::disconnect() {
    closesocket(sock);
}
