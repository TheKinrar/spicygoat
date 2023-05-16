//
// Created by thekinrar on 02/04/19.
//

#include <spicygoat/protocol/packets/play/clientbound/PacketSpawnPosition.h>

PacketSpawnPosition::PacketSpawnPosition(Position position)
    : ClientBoundPacket(Packets::C_SPAWN_POSITION), position(position) {}

std::vector<std::byte> PacketSpawnPosition::bytes() const {
    std::vector<std::byte> array;
    PacketData::writePosition(position, array);
    PacketData::writeFloat(0, array);  // TODO spawn angle? only one?
    return array;
}

std::string PacketSpawnPosition::toString() const {
    return std::string("PacketSpawnPosition{") + position.toString() + "}";
}
