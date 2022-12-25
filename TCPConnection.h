//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_TCPCONNECTION_H
#define SPICYGOAT_TCPCONNECTION_H

#include <netinet/in.h>
#include <thread>
#include <mutex>

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

    ProtocolState getState() const;
    void setState(ProtocolState newState);

    std::string getName();

    void sendPacket(Packet* packet);
    void disconnect();

    EntityPlayer* getPlayer();
    void setPlayer(EntityPlayer* newPlayer);

    const PacketListener& getListener() const;
    void setListener(std::unique_ptr<PacketListener> newListener);

    void task();

    void keepAlive(int64_t millis);
    void confirmKeepAlive(int64_t id);

    std::string username;
    uuid_t uuid;

private:
    int sock;
    sockaddr_in addr;

    std::thread *thread;

    std::mutex m_send;

    std::mutex m_keepAlive;
    int64_t latestKeepAlive = 0;
    bool keepAliveOk = true;

    ProtocolState state = ProtocolState::HANDSHAKE;
    std::unique_ptr<PacketListener> listener;

    EntityPlayer *player;

    int readVarInt();
};


#endif //SPICYGOAT_TCPCONNECTION_H
