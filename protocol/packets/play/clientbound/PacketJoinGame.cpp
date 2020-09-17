//
// Created by thekinrar on 01/04/19.
//

#include "PacketJoinGame.h"

PacketJoinGame::PacketJoinGame(EntityPlayer *player) {
    this->player = player;
}

std::vector<std::byte> PacketJoinGame::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x24, array);
    PacketData::writeInt(player->getEID(), array);
    PacketData::writeUnsignedByte(0, array); // TODO gamemode
    PacketData::writeUnsignedByte(0, array); // TODO prev gamemode

    // TODO world names []
    PacketData::writeVarInt(1, array);
    PacketData::writeString("default_world", array);

    // TODO dimension codec - REQUIRED FOR 1.16.3 - this will NOT work
    PacketData::writeInt(0, array);

    PacketData::writeString("default_world", array); // TODO current world name

    PacketData::writeLong(0, array); // TODO first 8B of sha-256 hash of seed
    PacketData::writeVarInt(1, array); // TODO max players
    PacketData::writeVarInt(10, array); // TODO view distance
    PacketData::writeBoolean(false, array); // TODO reduced debug info
    PacketData::writeBoolean(true, array); // TODO enable respawn screen (false if doImmediateRespawn gamerule)
    PacketData::writeBoolean(false, array); // TODO debug mode
    PacketData::writeBoolean(false, array); // TODO superflat
    return array;
}

std::string PacketJoinGame::toString() const {
    return std::string("PacketJoinGame{player=") + player->toString() + "}";
}
