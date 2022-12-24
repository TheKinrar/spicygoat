//
// Created by thekinrar on 02/04/19.
//

#include "PacketSpawnPosition.h"

PacketSpawnPosition::PacketSpawnPosition(Position position) : position(position) {}

std::vector<std::byte> PacketSpawnPosition::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x4C, array);
    PacketData::writePosition(position, array);
    PacketData::writeFloat(0, array); // TODO spawn angle? only one?
    return array;
}

std::string PacketSpawnPosition::toString() const {
    return std::string("PacketSpawnPosition{") + position.toString() + "}";
}
