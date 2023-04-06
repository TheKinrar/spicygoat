//
// Created by thekinrar on 19/09/2020.
//

#include <spicygoat/protocol/packets/play/clientbound/PacketEntityTeleport.h>

PacketEntityTeleport::PacketEntityTeleport(int32_t eid, const Location &loc, bool onGround)
    : ClientBoundPacket(Packets::C_TELEPORT_ENTITY), eid(eid), loc(loc), onGround(onGround) {}

std::vector<std::byte> PacketEntityTeleport::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeVarInt(eid, array);
    PacketData::writeDouble(loc.getX(), array);
    PacketData::writeDouble(loc.getY(), array);
    PacketData::writeDouble(loc.getZ(), array);
    PacketData::writeAngle(loc.getYaw(), array);
    PacketData::writeAngle(loc.getPitch(), array);
    PacketData::writeBoolean(onGround, array);
    return array;
}

std::string PacketEntityTeleport::toString() const {
    return std::string("PacketEntityTeleport{eid=") + std::to_string(eid) + ",...}";
}
