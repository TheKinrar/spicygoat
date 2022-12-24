//
// Created by thekinrar on 19/09/2020.
//

#include "PacketEntityTeleport.h"

PacketEntityTeleport::PacketEntityTeleport(int32_t eid, const Location &loc, bool onGround) : ClientBoundPacket(0x56), eid(eid), loc(loc), onGround(onGround) {}

std::vector<std::byte> PacketEntityTeleport::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x64, array);
    PacketData::writeVarInt(eid, array);
    PacketData::writeDouble(loc.getX(), array);
    PacketData::writeDouble(loc.getY(), array);
    PacketData::writeDouble(loc.getZ(), array);
    PacketData::writeByte(loc.getYaw(), array);
    PacketData::writeByte(loc.getPitch(), array);
    PacketData::writeBoolean(onGround, array);
    return array;
}

std::string PacketEntityTeleport::toString() const {
    return std::string("PacketEntityTeleport{eid=") + std::to_string(eid) + ",...}";
}
