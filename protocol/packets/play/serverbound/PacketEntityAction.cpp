//
// Created by thekinrar on 04/04/19.
//

#include "PacketEntityAction.h"

PacketEntityAction::PacketEntityAction(PacketData *data) : ServerBoundPacket(Packets::S_ENTITY_ACTION) {
    eid = data->readVarInt();
    action = data->readVarInt();
    jumpBoost = data->readVarInt();
}

std::string PacketEntityAction::toString() const {
    return std::string("PacketEntityAction{eid=") + std::to_string(eid)
           + ",action=" + std::to_string(action)
           + ",jumpBoost=" + std::to_string(jumpBoost) + "}";
}
