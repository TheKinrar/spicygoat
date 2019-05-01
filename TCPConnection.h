//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_TCPCONNECTION_H
#define SPICYGOAT_TCPCONNECTION_H

class Packet;
class EntityPlayer;

#include "protocol/PacketData.h"
#include "protocol/ConnectionState.h"
#include "protocol/packets/Packet.h"
#include "entities/EntityPlayer.h"

#include <netinet/in.h>
#include <thread>
#include <mutex>

class TCPConnection {
public:
    TCPConnection(int sock, sockaddr_in addr);

    ConnectionState getState() const;
    void setState(ConnectionState newState);

    std::string getName();

    void sendPacket(Packet* packet);

    EntityPlayer* getPlayer();
    void setPlayer(EntityPlayer* newPlayer);

    void task();

    void keepAlive(int64_t millis);
    void confirmKeepAlive(int64_t id);
private:
    int sock;
    sockaddr_in addr;

    std::thread *thread;

    std::mutex m_send;

    std::mutex m_keepAlive;
    int64_t latestKeepAlive = 0;
    bool keepAliveOk = true;

    ConnectionState state = ConnectionState::HANDSHAKE;

    EntityPlayer *player;

    int readVarInt();
};


#endif //SPICYGOAT_TCPCONNECTION_H
