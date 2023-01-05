//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_TCPCONNECTION_H
#define SPICYGOAT_TCPCONNECTION_H

#include <thread>
#include <mutex>
#include <utility>

#ifdef __linux__
#include <netinet/in.h>
#define closesocket close
#endif

#ifdef _WIN64
#include <winsock2.h>
#endif

class EntityPlayer;
class PacketListener;

#include "protocol.h"
#include "network/PacketListener.h"
#include "entities/EntityPlayer.h"

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

    std::shared_ptr<EntityPlayer> getPlayer() {
        return player;
    }
    void setPlayer(std::shared_ptr<EntityPlayer> newPlayer) {
        this->player = std::move(newPlayer);
    }

    const PacketListener& getListener() const;
    void setListener(std::unique_ptr<PacketListener> newListener);

    void task();

    void keepAlive(int64_t millis);
    void confirmKeepAlive(int64_t id);

    std::string username;
    uuids::uuid uuid;

    bool alive = true;

private:
    int sock;
    sockaddr_in addr;

    std::unique_ptr<std::thread> thread;

    std::mutex m_send;

    std::mutex m_keepAlive;
    int64_t latestKeepAlive = 0;
    bool keepAliveOk = true;

    ProtocolState state = ProtocolState::HANDSHAKE;
    std::unique_ptr<PacketListener> listener;

    std::shared_ptr<EntityPlayer> player;

    int readVarInt();
};


#endif //SPICYGOAT_TCPCONNECTION_H
