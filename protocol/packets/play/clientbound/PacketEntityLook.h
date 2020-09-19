//
// Created by thekinrar on 19/09/2020.
//

#ifndef SPICYGOAT_PACKETENTITYLOOK_H
#define SPICYGOAT_PACKETENTITYLOOK_H


#include "../../ClientBoundPacket.h"
#include "../../../../world/geo/Location.h"

class PacketEntityLook : public ClientBoundPacket {
public:
    PacketEntityLook(int32_t eid, Location &from, Location &to, bool onGround);

    std::vector<std::byte> bytes() override;

    std::string toString() const override;

private:
    int32_t eid;
    Location &from, &to;
    bool onGround;
};


#endif //SPICYGOAT_PACKETENTITYLOOK_H
