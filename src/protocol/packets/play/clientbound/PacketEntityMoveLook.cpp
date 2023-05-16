//
// Created by thekinrar on 07/05/19.
//

#include <spicygoat/protocol/packets/play/clientbound/PacketEntityMoveLook.h>

PacketEntityMoveLook::PacketEntityMoveLook(int32_t eid, double dx, double dy, double dz, float yaw, float pitch,
                                           bool onGround)
    : ClientBoundPacket(Packets::C_ENTITY_MOVE_LOOK),
      eid(eid),
      dx(dx),
      dy(dy),
      dz(dz),
      yaw(yaw),
      pitch(pitch),
      onGround(onGround) {}

std::vector<std::byte> PacketEntityMoveLook::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeVarInt(eid, array);
    PacketData::writeShort((int16_t)dx, array);
    PacketData::writeShort((int16_t)dy, array);
    PacketData::writeShort((int16_t)dz, array);
    PacketData::writeAngle(yaw, array);
    PacketData::writeAngle(pitch, array);
    PacketData::writeBoolean(onGround, array);
    return array;
}

std::string PacketEntityMoveLook::toString() const {
    return std::string("PacketEntityMoveLook{eid=") + std::to_string(eid) + ",...}";
}
