//
// Created by thekinrar on 04/04/19.
//

#include "PacketPlayerAbilitiesSB.h"

PacketPlayerAbilitiesSB::PacketPlayerAbilitiesSB(PacketData *data, TCPConnection *conn) : conn(conn) {
    flying = data->readUnsignedByte() & 0x02u;
}

void PacketPlayerAbilitiesSB::handle() {
    // TODO
}

std::string PacketPlayerAbilitiesSB::toString() const {
    return std::string("PacketPlayerAbilitiesSB{unparsed}");
}
