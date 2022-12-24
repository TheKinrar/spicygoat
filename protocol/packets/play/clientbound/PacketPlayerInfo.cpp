//
// Created by thekinrar on 07/05/19.
//

#include "PacketPlayerInfo.h"
#include <iostream>

PacketPlayerInfo::PacketPlayerInfo(PacketPlayerInfo::Action action, std::forward_list<EntityPlayer*> &players) : ClientBoundPacket(0x32), action(action), players(players) {}

std::vector<std::byte> PacketPlayerInfo::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x36, array);

    if(action != Action::AddPlayer)
      throw std::runtime_error("Only AddPlayer is supported");

    std::bitset<6> actionsMask;
    actionsMask.set(0); // AddPlayer

    PacketData::writeFixedBitSet(actionsMask, array);
    PacketData::writeVarInt(std::distance(players.begin(), players.end()), array);

    for(auto player : players) {
        PacketData::writeUuid(player->getUuid(), array);

        switch(action) {
            case Action::AddPlayer:
                PacketData::writeString(player->getName(), array);
                PacketData::writeVarInt(0, array); // TODO properties
                break;
            case Action::UpdateGamemode:
                PacketData::writeVarInt(0, array); // TODO gamemode
                break;
            case Action::UpdateLatency:
                PacketData::writeVarInt(0, array); // TODO ping
                break;
            case Action::UpdateDisplayName:
                PacketData::writeBoolean(false, array); // TODO display name
                break;
            case Action::RemovePlayer:
                break; // no fields
        }
    }

    return array;
}

std::string PacketPlayerInfo::toString() const {
    return std::string("PacketPlayerInfo{action=") + std::to_string(action)
           + ",count=" + std::to_string(std::distance(players.begin(), players.end()))
           + ",...}";
}
