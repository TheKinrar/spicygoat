//
// Created by thekinrar on 31/03/19.
//

#include <spicygoat/protocol/packets/status/PacketPong.h>

PacketPong::PacketPong(int64_t payload) {
    this->payload = payload;
}

std::vector<std::byte> PacketPong::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x01, array);
    PacketData::writeLong(payload, array);
    return array;
}

std::string PacketPong::toString() const {
    return std::string("PacketPong{payload=" + std::to_string(payload) + "}");
}
