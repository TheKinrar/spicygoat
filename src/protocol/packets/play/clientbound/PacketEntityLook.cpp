//
// Created by thekinrar on 19/09/2020.
//

#include <spicygoat/protocol/packets/play/clientbound/PacketEntityLook.h>

PacketEntityLook::PacketEntityLook(int32_t eid, Location &from, Location &to, bool onGround)
    : ClientBoundPacket(Packets::C_ENTITY_LOOK), eid(eid), from(from), to(to), onGround(onGround) {}

std::vector<std::byte> PacketEntityLook::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeVarInt(eid, array);
    PacketData::writeAngle(to.getYaw(), array);
    PacketData::writeAngle(to.getPitch(), array);
    PacketData::writeBoolean(onGround, array);
    return array;
}

std::string PacketEntityLook::toString() const {
    return std::string("PacketEntityLook{eid=") + std::to_string(eid) + ",...}";
}
