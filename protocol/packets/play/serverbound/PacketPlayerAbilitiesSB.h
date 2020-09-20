//
// Created by thekinrar on 04/04/19.
//

#ifndef SPICYGOAT_PACKETPLAYERABILITIESSB_H
#define SPICYGOAT_PACKETPLAYERABILITIESSB_H


#include "../../ServerBoundPacket.h"

class PacketPlayerAbilitiesSB : public ServerBoundPacket {
public:
    explicit PacketPlayerAbilitiesSB(PacketData* data);

    std::string toString() const override;

    bool flying;
};


#endif//SPICYGOAT_PACKETPLAYERABILITIESSB_H
