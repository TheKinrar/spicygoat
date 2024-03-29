//
// Created by thekinrar on 05/01/23.
//

#ifndef SPICYGOAT_PACKETBLOCKUPDATE_H
#define SPICYGOAT_PACKETBLOCKUPDATE_H

#include <spicygoat/protocol/ClientBoundPacket.h>

class PacketBlockUpdate : public ClientBoundPacket {
   public:
    Position position;
    int id;

    PacketBlockUpdate(const Position &position, int id)
        : ClientBoundPacket(Packets::C_BLOCK_UPDATE), position(position), id(id) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;
        PacketData::writePosition(position, array);
        PacketData::writeVarInt(id, array);
        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return std::string("PacketBlockUpdate{}");
    }
};

#endif  // SPICYGOAT_PACKETBLOCKUPDATE_H
