//
// Created by thekinrar on 02/04/19.
//

#include "PacketKeepAliveSB.h"

PacketKeepAliveSB::PacketKeepAliveSB(PacketData *data, TCPConnection *conn) : conn(conn) {
    this->id = data->readLong();
}

void PacketKeepAliveSB::handle() {
    conn->confirmKeepAlive(id);
}

std::string PacketKeepAliveSB::toString() const {
    return std::string("PacketKeepAliveSB{id=") + std::to_string(id) + "}";
}
