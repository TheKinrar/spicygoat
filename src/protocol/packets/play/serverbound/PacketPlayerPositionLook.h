//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETPLAYERLOCATIONSB_H
#define SPICYGOAT_PACKETPLAYERLOCATIONSB_H

#include "../../ServerBoundPacket.h"

class PacketPlayerPositionLook : public ServerBoundPacket {
   public:
    explicit PacketPlayerPositionLook(PacketData& data);

    std::string toString() const override;

    double x, y, z;
    float yaw, pitch;
    bool onGround;
};

#endif  // SPICYGOAT_PACKETPLAYERLOCATIONSB_H
