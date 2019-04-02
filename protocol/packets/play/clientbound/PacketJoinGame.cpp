//
// Created by thekinrar on 01/04/19.
//

#include "PacketJoinGame.h"

PacketJoinGame::PacketJoinGame(EntityPlayer *player) {
    this->player = player;
}

std::vector<std::byte> PacketJoinGame::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x25, array);
    PacketData::writeInt(player->getEID(), array);
    PacketData::writeUnsignedByte(0, array); // TODO gamemode
    PacketData::writeInt(0, array); // TODO dimension
    PacketData::writeUnsignedByte(0, array); // TODO difficulty
    PacketData::writeUnsignedByte(1, array); // TODO max players (uint8_t!)
    PacketData::writeString("default", array); // TODO level type
    PacketData::writeBoolean(false, array); // TODO reduced debug info (?)
    return array;
}

std::string PacketJoinGame::toString() const {
    return std::string("PacketJoinGame{player=") + player->toString() + "}";
}
