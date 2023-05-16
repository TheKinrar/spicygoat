//
// Created by thekinrar on 19/09/2020.
//

#include <spicygoat/protocol/packets/play/clientbound/PacketEntityMove.h>

PacketEntityMove::PacketEntityMove(int32_t eid, double dx, double dy, double dz, bool onGround)
    : ClientBoundPacket(Packets::C_ENTITY_MOVE), eid(eid), dx(dx), dy(dy), dz(dz), onGround(onGround) {}

std::vector<std::byte> PacketEntityMove::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeVarInt(eid, array);
    PacketData::writeShort((int16_t)dx, array);
    PacketData::writeShort((int16_t)dy, array);
    PacketData::writeShort((int16_t)dz, array);
    PacketData::writeBoolean(onGround, array);
    return array;
}

std::string PacketEntityMove::toString() const {
    return std::string("PacketEntityMove{eid=") + std::to_string(eid) + ",...}";
}
