//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_PACKET_H
#define SPICYGOAT_PACKET_H

class TCPConnection;

#include "../PacketData.h"
#include "../../TCPConnection.h"

class Packet {
public:
    static Packet* parse(PacketData* data, TCPConnection* conn);

    virtual void handle() = 0;
    virtual std::vector<std::byte> bytes() = 0;

    virtual std::string toString() const = 0;
};


#endif //SPICYGOAT_PACKET_H
