//
// Created by thekinrar on 07/05/19.
//

#include "PacketEntityMoveLook.h"

PacketEntityMoveLook::PacketEntityMoveLook(int32_t eid, Location &from, Location &to, bool onGround) : eid(eid), from(from), to(to), onGround(onGround) {}

std::vector<std::byte> PacketEntityMoveLook::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x29, array);
    PacketData::writeVarInt(eid, array);
    PacketData::writeShort((int16_t) ((to.getX() - from.getX()) * 4096), array);
    PacketData::writeShort((int16_t) ((to.getY() - from.getY()) * 4096), array);
    PacketData::writeShort((int16_t) ((to.getZ() - from.getZ()) * 4096), array);
    PacketData::writeByte(0, array); // TODO wtf yaw
    PacketData::writeByte(0, array); // TODO wtf pitch
    PacketData::writeBoolean(onGround, array);
    return array;
}

std::string PacketEntityMoveLook::toString() const {
    return std::string("PacketEntityMoveLook{eid=") + std::to_string(eid) + ",...}";
}
