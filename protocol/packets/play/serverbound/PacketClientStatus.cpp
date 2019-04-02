//
// Created by thekinrar on 02/04/19.
//

#include "PacketClientStatus.h"

PacketClientStatus::PacketClientStatus(PacketData *data, TCPConnection *conn) : conn(conn) {
    this->action = data->readVarInt();
}

void PacketClientStatus::handle() {
    // TODO perform respawn (?) and handle stats request
}

std::string PacketClientStatus::toString() const {
    return std::string("PacketClientStatus{action=") + std::to_string(action) + "}";
}
