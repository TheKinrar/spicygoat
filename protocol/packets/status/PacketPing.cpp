//
// Created by thekinrar on 31/03/19.
//

#include "PacketPing.h"
#include "PacketPong.h"

PacketPing::PacketPing(PacketData *data, TCPConnection *conn) {
    this->conn = conn;

    payload = data->readLong();
}

int64_t PacketPing::getPayload() const {
    return payload;
}

std::string PacketPing::toString() const {
    return std::string("PacketPing{payload=") + std::to_string(payload) + "}";
}

void PacketPing::handle() {
    conn->sendPacket(new PacketPong(payload));
}
