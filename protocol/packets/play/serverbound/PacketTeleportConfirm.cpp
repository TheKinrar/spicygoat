//
// Created by thekinrar on 02/04/19.
//

#include "PacketTeleportConfirm.h"

PacketTeleportConfirm::PacketTeleportConfirm(PacketData *data, TCPConnection *conn) : conn(conn) {
    this->tpId = data->readVarInt();
}

void PacketTeleportConfirm::handle() {
    // TODO confirm TP
}

std::string PacketTeleportConfirm::toString() const {
    return std::string("PacketTeleportConfirm{id=") + std::to_string(tpId) + "}";
}
