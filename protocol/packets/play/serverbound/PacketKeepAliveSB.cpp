//
// Created by thekinrar on 02/04/19.
//

#include "PacketKeepAliveSB.h"

PacketKeepAliveSB::PacketKeepAliveSB(PacketData *data) : ServerBoundPacket(Packets::S_KEEP_ALIVE) {
    this->id = data->readLong();
}

std::string PacketKeepAliveSB::toString() const {
    return std::string("PacketKeepAliveSB{id=") + std::to_string(id) + "}";
}
