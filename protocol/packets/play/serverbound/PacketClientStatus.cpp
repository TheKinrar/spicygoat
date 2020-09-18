//
// Created by thekinrar on 02/04/19.
//

#include "PacketClientStatus.h"

PacketClientStatus::PacketClientStatus(PacketData *data) : ServerBoundPacket(Packets::S_CLIENT_STATUS) {
    this->action = data->readVarInt();
}

std::string PacketClientStatus::toString() const {
    return std::string("PacketClientStatus{action=") + std::to_string(action) + "}";
}
