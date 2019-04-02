//
// Created by thekinrar on 02/04/19.
//

#include "PacketPlayerPositionLook.h"

PacketPlayerPositionLook::PacketPlayerPositionLook(PacketData *data, TCPConnection *conn) : conn(conn) {
    x = data->readDouble();
    y = data->readDouble();
    z = data->readDouble();
    yaw = data->readFloat();
    pitch = data->readFloat();
    onGround = data->readBoolean();
}

void PacketPlayerPositionLook::handle() {
    conn->getPlayer()->setNextPosition(x, y, z);
    conn->getPlayer()->setNextLook(yaw, pitch);
    conn->getPlayer()->setNextOnGround(onGround);
}

std::string PacketPlayerPositionLook::toString() const {
    return std::string("PacketPlayerPositionLook{x=") + std::to_string(x)
            + ",y=" + std::to_string(y)
            + ",z=" + std::to_string(z)
            + ",yaw=" + std::to_string(yaw)
            + ",pitch=" + std::to_string(pitch)
            + ",onGround=" + std::to_string(onGround) + "}";
}
