//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_PACKETLISTENERHANDSHAKE_H
#define SPICYGOAT_PACKETLISTENERHANDSHAKE_H

#include "PacketListener.h"

class PacketListenerHandshake : public PacketListener {
   public:
    void handle(const ServerBoundPacket &packet) override;

    virtual void onHandshake(const PacketHandshake &) = 0;
};

#endif  // SPICYGOAT_PACKETLISTENERHANDSHAKE_H
