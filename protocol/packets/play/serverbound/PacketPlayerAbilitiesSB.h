//
// Created by thekinrar on 04/04/19.
//

#ifndef SPICYGOAT_PACKETPLAYERABILITIESSB_H
#define SPICYGOAT_PACKETPLAYERABILITIESSB_H


#include "../../ServerBoundPacket.h"

class PacketPlayerAbilitiesSB : public ServerBoundPacket {
public:
    explicit PacketPlayerAbilitiesSB(PacketData* data, TCPConnection* conn);

    void handle() override;

    std::string toString() const override;

private:
    TCPConnection* conn;

    bool invulnerable;
    bool flying;
    bool allowFlying;
    bool creative;

    float flyingSpeed;
    float walkingSpeed;
};


#endif //SPICYGOAT_PACKETPLAYERABILITIESSB_H
