//
// Created by thekinrar on 04/04/19.
//

#include "PacketPlayerAbilitiesSB.h"

PacketPlayerAbilitiesSB::PacketPlayerAbilitiesSB(PacketData *data, TCPConnection *conn) : conn(conn) {
    data->readByte();
    flyingSpeed = data->readFloat();
    walkingSpeed = data->readFloat();
}

void PacketPlayerAbilitiesSB::handle() {
    // TODO
}

std::string PacketPlayerAbilitiesSB::toString() const {
    return std::string("PacketPlayerAbilitiesSB{unparsed}");
}
