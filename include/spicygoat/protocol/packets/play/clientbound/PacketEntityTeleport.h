//
// Created by thekinrar on 19/09/2020.
//

#ifndef SPICYGOAT_PACKETENTITYTELEPORT_H
#define SPICYGOAT_PACKETENTITYTELEPORT_H

#include <spicygoat/protocol/ClientBoundPacket.h>
#include <spicygoat/world/geo/Location.h>

class PacketEntityTeleport : public ClientBoundPacket {
   public:
    PacketEntityTeleport(int32_t eid, const Location &loc, bool onGround);

    std::vector<std::byte> bytes() const override;

    std::string toString() const override;

   private:
    int32_t eid;
    Location loc;
    bool onGround;
};

#endif  // SPICYGOAT_PACKETENTITYTELEPORT_H
