//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_TCPCONNECTION_H
#define SPICYGOAT_TCPCONNECTION_H

#include <mutex>
#include <thread>
#include <utility>

#ifdef __linux__
#include <arpa/inet.h>
#include <netinet/in.h>
#define closesocket close
#endif

#ifdef _WIN64
#include <winsock2.h>
#endif

class EntityPlayer;
class PacketListener;

#include "entities/types/EntityPlayer.h"
#include "network/PacketListener.h"
#include "protocol.h"
#include "spdlog/logger.h"

class TCPConnection {
   public:
    TCPConnection(int sock, sockaddr_in addr);
    TCPConnection(const TCPConnection&) = delete;
    void operator=(const TCPConnection&) = delete;
    virtual ~TCPConnection() {
        thread->join();
    }

    ProtocolState getState() const;
    void setState(ProtocolState newState);

    std::string getName();

    void sendPacket(const Packet& packet);
    void disconnect();

    void setPlayer(const std::shared_ptr<EntityPlayer>& newPlayer) {
        this->player = newPlayer;
    }

    spdlog::logger& getLogger() const {
        return *logger;
    }

    PacketListener& getListener() const;
    void setListener(std::unique_ptr<PacketListener> newListener);

    void task();

    void keepAlive(int64_t millis);
    void confirmKeepAlive(int64_t id);

    std::string username;
    uuids::uuid uuid;

    bool alive = true;

   private:
    std::shared_ptr<spdlog::logger> logger;

    int sock;
    sockaddr_in addr;

    std::unique_ptr<std::thread> thread;

    std::mutex m_send;

    std::mutex m_keepAlive;
    int64_t latestKeepAlive = 0;
    bool keepAliveOk = true;

    ProtocolState state = ProtocolState::HANDSHAKE;
    std::unique_ptr<PacketListener> listener;

    std::weak_ptr<EntityPlayer> player;

    int readVarInt();
};

#endif  // SPICYGOAT_TCPCONNECTION_H
