//
// Created by thekinrar on 02/04/19.
//

#include <spicygoat/protocol/packets/play/serverbound/PacketPlayerPositionLook.h>

PacketPlayerPositionLook::PacketPlayerPositionLook(PacketData& data)
    : ServerBoundPacket(Packets::S_PLAYER_POSITION_LOOK) {
    x = data.readDouble();
    y = data.readDouble();
    z = data.readDouble();
    yaw = data.readFloat();
    pitch = data.readFloat();
    onGround = data.readBoolean();
}

std::string PacketPlayerPositionLook::toString() const {
    return std::string("PacketPlayerPositionLook{x=") + std::to_string(x) + ",y=" + std::to_string(y) +
           ",z=" + std::to_string(z) + ",yaw=" + std::to_string(yaw) + ",pitch=" + std::to_string(pitch) +
           ",onGround=" + std::to_string(onGround) + "}";
}
