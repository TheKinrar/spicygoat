//
// Created by thekinrar on 31/03/19.
//

#include "PacketLoginStart.h"
#include "../../packets.h"

PacketLoginStart::PacketLoginStart(PacketData* data) : ServerBoundPacket(Packets::S_LOGIN_START) {
    this->name = data->readString();
}

std::string PacketLoginStart::toString() const {
    return std::string("PacketLoginStart{name=") + name + "}";
}
