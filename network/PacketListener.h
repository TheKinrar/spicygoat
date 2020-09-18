//
// Created by thekinrar on 17/09/2020.
//

#ifndef SPICYGOAT_PACKETLISTENER_H
#define SPICYGOAT_PACKETLISTENER_H


#include "../protocol/packets.h"

class PacketListener {
public:
    virtual void handle(const ServerBoundPacket&) = 0;
};


#endif //SPICYGOAT_PACKETLISTENER_H
