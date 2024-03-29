//
// Created by thekinrar on 31/03/19.
//

#include <spicygoat/protocol/packets/login/PacketLoginStart.h>

PacketLoginStart::PacketLoginStart(PacketData& data) : ServerBoundPacket(Packets::S_LOGIN_START) {
    this->name = data.readString();
    this->hasUuid = data.readBoolean();
    if(hasUuid) {
        this->uuid = data.readUuid();
    }
}

std::string PacketLoginStart::toString() const {
    if(hasUuid) {
        return std::string("PacketLoginStart{name=") + name + ",hasUuid=" + std::to_string(hasUuid) +
               ",uuid=" + to_string(uuid) + "}";
    } else {
        return std::string("PacketLoginStart{name=") + name + ",hasUuid=" + std::to_string(hasUuid) + "}";
    }
}
