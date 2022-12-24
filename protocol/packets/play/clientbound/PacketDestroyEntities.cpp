//
// Created by thekinrar on 19/09/2020.
//

#include "PacketDestroyEntities.h"

PacketDestroyEntities::PacketDestroyEntities(int32_t eid) : ClientBoundPacket(0x36), eid(eid) {}

std::vector<std::byte> PacketDestroyEntities::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x3A, array);
    PacketData::writeVarInt(1, array);
    PacketData::writeVarInt(eid, array);
    return array;
}

std::string PacketDestroyEntities::toString() const {
    return std::string("PacketDestroyEntities{eid=") + std::to_string(eid) + "}";
}
