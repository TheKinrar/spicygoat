//
// Created by thekinrar on 02/04/19.
//

#include "PacketServerDifficulty.h"

PacketServerDifficulty::PacketServerDifficulty(uint8_t difficulty) {
    this->difficulty = difficulty;
}

std::vector<std::byte> PacketServerDifficulty::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x0D, array);
    PacketData::writeUnsignedByte(0, array);
    return array;
}

std::string PacketServerDifficulty::toString() const {
    return std::string("PacketServerDifficulty{difficulty=") + std::to_string(difficulty) + "}";
}
