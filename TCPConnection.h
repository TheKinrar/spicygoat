//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_TCPCONNECTION_H
#define SPICYGOAT_TCPCONNECTION_H

class Packet;

#include "protocol/PacketData.h"
#include "protocol/ConnectionState.h"
#include "protocol/packets/Packet.h"
#include "entities/EntityPlayer.h"

#include <netinet/in.h>

class TCPConnection {
public:
    TCPConnection(int sock, sockaddr_in addr);

    ConnectionState getState() const;
    void setState(ConnectionState newState);

    std::string getName();

    void sendPacket(Packet* packet);

    void setPlayer(EntityPlayer* newPlayer);

    void task();
private:
    int sock;
    sockaddr_in addr;

    ConnectionState state = ConnectionState::HANDSHAKE;

    EntityPlayer *player;

    int readVarInt();
};


#endif //SPICYGOAT_TCPCONNECTION_H
