//
// Created by thekinrar on 04/04/19.
//

#include "PacketPlayerAbilitiesSB.h"

PacketPlayerAbilitiesSB::PacketPlayerAbilitiesSB(PacketData *data) : ServerBoundPacket(Packets::S_PLAYER_ABILITIES) {
    flying = data->readUnsignedByte() & 0x02u;
}

std::string PacketPlayerAbilitiesSB::toString() const {
    return std::string("PacketPlayerAbilitiesSB{unparsed}");
}
