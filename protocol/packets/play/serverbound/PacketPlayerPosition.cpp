//
// Created by thekinrar on 02/04/19.
//

#include "PacketPlayerPosition.h"

PacketPlayerPosition::PacketPlayerPosition(PacketData *data, TCPConnection *conn) : conn(conn) {
    x = data->readDouble();
    y = data->readDouble();
    z = data->readDouble();
    onGround = data->readBoolean();
}

void PacketPlayerPosition::handle() {
    conn->getPlayer()->setNextPosition(x, y, z);
    conn->getPlayer()->setNextOnGround(onGround);
}

std::string PacketPlayerPosition::toString() const {
    return std::string("PacketPlayerPosition{x=") + std::to_string(x)
           + ",y=" + std::to_string(y)
           + ",z=" + std::to_string(z)
           + ",onGround=" + std::to_string(onGround) + "}";
}
