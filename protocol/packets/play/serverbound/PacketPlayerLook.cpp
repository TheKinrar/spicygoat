//
// Created by thekinrar on 02/04/19.
//

#include "PacketPlayerLook.h"

PacketPlayerLook::PacketPlayerLook(PacketData *data, TCPConnection *conn) : conn(conn) {
    yaw = data->readFloat();
    pitch = data->readFloat();
    onGround = data->readBoolean();
}

void PacketPlayerLook::handle() {
    conn->getPlayer()->setNextLook(yaw, pitch);
    conn->getPlayer()->setNextOnGround(onGround);
}

std::string PacketPlayerLook::toString() const {
    return std::string("PacketPlayerLook{yaw=") + std::to_string(yaw)
           + ",pitch=" + std::to_string(pitch)
           + ",onGround=" + std::to_string(onGround) + "}";
}
