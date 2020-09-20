//
// Created by thekinrar on 02/04/19.
//

#include "PacketPlayerLook.h"

PacketPlayerLook::PacketPlayerLook(PacketData *data) : ServerBoundPacket(Packets::S_PLAYER_LOOK) {
    yaw = data->readFloat();
    pitch = data->readFloat();
    onGround = data->readBoolean();
}

std::string PacketPlayerLook::toString() const {
    return std::string("PacketPlayerLook{yaw=") + std::to_string(yaw) + ",pitch=" + std::to_string(pitch) + ",onGround=" + std::to_string(onGround) + "}";
}
