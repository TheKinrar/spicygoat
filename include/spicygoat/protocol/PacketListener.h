//
// Created by thekinrar on 17/09/2020.
//

#ifndef SPICYGOAT_PACKETLISTENER_H
#define SPICYGOAT_PACKETLISTENER_H

#include <spicygoat/protocol/packets.h>

class PacketListener {
   public:
    virtual ~PacketListener() = default;
    virtual void handle(const ServerBoundPacket&) = 0;
    virtual void tick(){};
};

#endif  // SPICYGOAT_PACKETLISTENER_H
