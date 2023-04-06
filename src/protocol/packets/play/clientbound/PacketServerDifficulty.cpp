//
// Created by thekinrar on 02/04/19.
//

#include <spicygoat/protocol/packets/play/clientbound/PacketServerDifficulty.h>

PacketServerDifficulty::PacketServerDifficulty(uint8_t difficulty) : ClientBoundPacket(Packets::C_SERVER_DIFFICULTY) {
    this->difficulty = difficulty;
}

std::vector<std::byte> PacketServerDifficulty::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeUnsignedByte(0, array);
    PacketData::writeBoolean(false, array);  // TODO: difficulty locked?
    return array;
}

std::string PacketServerDifficulty::toString() const {
    return std::string("PacketServerDifficulty{difficulty=") + std::to_string(difficulty) + "}";
}
