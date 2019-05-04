//
// Created by thekinrar on 02/04/19.
//

#include "PacketKeepAliveCB.h"

PacketKeepAliveCB::PacketKeepAliveCB(int64_t id) : id(id) {}

std::vector<std::byte> PacketKeepAliveCB::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x20, array);
    PacketData::writeLong(id, array);
    return array;
}

std::string PacketKeepAliveCB::toString() const {
    return std::string("PacketKeepAliveCB{id=") + std::to_string(id) + "}";
}
