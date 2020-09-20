//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETPLAYERLOOK_H
#define SPICYGOAT_PACKETPLAYERLOOK_H


#include "../../ServerBoundPacket.h"

class PacketPlayerLook : public ServerBoundPacket {
public:
    explicit PacketPlayerLook(PacketData *data);

    std::string toString() const override;

    float yaw, pitch;
    bool onGround;
};


#endif//SPICYGOAT_PACKETPLAYERLOOK_H
