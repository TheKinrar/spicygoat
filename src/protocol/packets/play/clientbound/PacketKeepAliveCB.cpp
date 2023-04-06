//
// Created by thekinrar on 02/04/19.
//

#include <spicygoat/protocol/packets/play/clientbound/PacketKeepAliveCB.h>

PacketKeepAliveCB::PacketKeepAliveCB(int64_t id) : ClientBoundPacket(Packets::C_KEEP_ALIVE), id(id) {}

std::vector<std::byte> PacketKeepAliveCB::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeLong(id, array);
    return array;
}

std::string PacketKeepAliveCB::toString() const {
    return std::string("PacketKeepAliveCB{id=") + std::to_string(id) + "}";
}
