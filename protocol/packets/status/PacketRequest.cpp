//
// Created by thekinrar on 30/03/19.
//

#include "PacketRequest.h"
#include "PacketResponse.h"

PacketRequest::PacketRequest(PacketData *data, TCPConnection *conn) {
    this->conn = conn;
}

void PacketRequest::handle() {
    conn->sendPacket(new PacketResponse());
}

std::string PacketRequest::toString() const {
    return std::string("PacketRequest{}");
}
