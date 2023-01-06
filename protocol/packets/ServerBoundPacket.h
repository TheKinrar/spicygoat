//
// Created by thekinrar on 31/03/19.
//

#ifndef SPICYGOAT_SERVERBOUNDPACKET_H
#define SPICYGOAT_SERVERBOUNDPACKET_H

class Packet;

#include <vector>

#include "Packet.h"

class ServerBoundPacket : public Packet {
   public:
    explicit ServerBoundPacket(int id);

    std::vector<std::byte> bytes() const override;
};

#endif  // SPICYGOAT_SERVERBOUNDPACKET_H
