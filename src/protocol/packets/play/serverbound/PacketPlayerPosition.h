//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETPLAYERPOSITION_H
#define SPICYGOAT_PACKETPLAYERPOSITION_H

#include "../../ServerBoundPacket.h"

class PacketPlayerPosition : public ServerBoundPacket {
   public:
    explicit PacketPlayerPosition(PacketData& data);

    std::string toString() const override;

    double x, y, z;
    bool onGround;
};

#endif  // SPICYGOAT_PACKETPLAYERPOSITION_H
