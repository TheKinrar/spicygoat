//
// Created by thekinrar on 07/05/19.
//

#ifndef SPICYGOAT_PACKETENTITYMOVELOOK_H
#define SPICYGOAT_PACKETENTITYMOVELOOK_H


#include "../../ClientBoundPacket.h"

class PacketEntityMoveLook : public ClientBoundPacket {
public:
    explicit PacketEntityMoveLook(int32_t, Location&, Location&, bool);

    std::vector<std::byte> bytes() override;

    std::string toString() const override;

private:
    int32_t eid;
    Location &from, &to;
    bool onGround;
};


#endif //SPICYGOAT_PACKETENTITYMOVELOOK_H
