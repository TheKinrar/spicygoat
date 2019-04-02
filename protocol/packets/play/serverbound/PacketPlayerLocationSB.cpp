//
// Created by thekinrar on 02/04/19.
//

#include "PacketPlayerLocationSB.h"

PacketPlayerLocationSB::PacketPlayerLocationSB(PacketData *data, TCPConnection *conn) : conn(conn) {
    this->location = Location(data->readDouble(),
            data->readDouble(),
            data->readDouble(),
            data->readFloat(),
            data->readFloat());
    this->onGround = data->readBoolean();
}

void PacketPlayerLocationSB::handle() {
    // TODO set location, broadcast, etc.
}

std::string PacketPlayerLocationSB::toString() const {
    return std::string("PacketPlayerLocationSB{loc=") + location.toString()
            + ",onGround=" + std::to_string(onGround)
            + "}";
}
