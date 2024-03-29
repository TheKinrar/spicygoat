//
// Created by thekinrar on 19/09/2020.
//

#include <spicygoat/protocol/packets/play/clientbound/PacketDestroyEntities.h>

PacketDestroyEntities::PacketDestroyEntities(int32_t eid) : ClientBoundPacket(Packets::C_DESTROY_ENTITIES), eid(eid) {}

std::vector<std::byte> PacketDestroyEntities::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeVarInt(1, array);
    PacketData::writeVarInt(eid, array);
    return array;
}

std::string PacketDestroyEntities::toString() const {
    return std::string("PacketDestroyEntities{eid=") + std::to_string(eid) + "}";
}
