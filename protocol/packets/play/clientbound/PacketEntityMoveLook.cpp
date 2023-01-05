//
// Created by thekinrar on 07/05/19.
//

#include "PacketEntityMoveLook.h"

PacketEntityMoveLook::PacketEntityMoveLook(int32_t eid, double dx, double dy, double dz, float yaw, float pitch,
                                           bool onGround) : ClientBoundPacket(0x28), eid(eid), dx(dx), dy(dy), dz(dz), yaw(yaw), pitch(pitch),
                                                            onGround(onGround) {}

std::vector<std::byte> PacketEntityMoveLook::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x28, array);
    PacketData::writeVarInt(eid, array);
    PacketData::writeShort((int16_t) (dx * 4096), array);
    PacketData::writeShort((int16_t) (dy * 4096), array);
    PacketData::writeShort((int16_t) (dz * 4096), array);
    PacketData::writeAngle(yaw, array);
    PacketData::writeAngle(pitch, array);
    PacketData::writeBoolean(onGround, array);
    return array;
}

std::string PacketEntityMoveLook::toString() const {
    return std::string("PacketEntityMoveLook{eid=") + std::to_string(eid) + ",...}";
}
