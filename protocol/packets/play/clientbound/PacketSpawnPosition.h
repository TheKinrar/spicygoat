//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETSPAWNPOSITION_H
#define SPICYGOAT_PACKETSPAWNPOSITION_H

#include "../../../../world/geo/Position.h"
#include "../../ClientBoundPacket.h"


class PacketSpawnPosition : public ClientBoundPacket {
public:
    explicit PacketSpawnPosition(Position position);

    std::vector<std::byte> bytes() override;

    std::string toString() const override;

private:
    Position position;
};


#endif//SPICYGOAT_PACKETSPAWNPOSITION_H
