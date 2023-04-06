//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETPLAYERLOCATIONCB_H
#define SPICYGOAT_PACKETPLAYERLOCATIONCB_H

#include <spicygoat/protocol/ClientBoundPacket.h>
#include <spicygoat/world/geo/Location.h>

class PacketPlayerLocationCB : public ClientBoundPacket {
   public:
    explicit PacketPlayerLocationCB(Location location);

    std::vector<std::byte> bytes() const override;

    std::string toString() const override;

   private:
    Location location;
};

#endif  // SPICYGOAT_PACKETPLAYERLOCATIONCB_H
