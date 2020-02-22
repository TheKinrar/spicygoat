//
// Created by thekinrar on 02/04/19.
//

#include "PacketSpawnPosition.h"

PacketSpawnPosition::PacketSpawnPosition(Position position) : position(position) {}

std::vector<std::byte> PacketSpawnPosition::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x4E, array);
    PacketData::writePosition(position, array);
    return array;
}

std::string PacketSpawnPosition::toString() const {
    return std::string("PacketSpawnPosition{") + position.toString() + "}";
}
