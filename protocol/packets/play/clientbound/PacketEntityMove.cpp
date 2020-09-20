//
// Created by thekinrar on 19/09/2020.
//

#include "PacketEntityMove.h"

PacketEntityMove::PacketEntityMove(int32_t eid, double dx, double dy, double dz, bool onGround) : ClientBoundPacket(
        0x27), eid(eid), dx(dx),
                                                                                                  dy(dy), dz(dz),
                                                                                                  onGround(onGround) {}

std::vector<std::byte> PacketEntityMove::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x27, array);
    PacketData::writeVarInt(eid, array);
    PacketData::writeShort((int16_t) (dx * 4096), array);
    PacketData::writeShort((int16_t) (dy * 4096), array);
    PacketData::writeShort((int16_t) (dz * 4096), array);
    PacketData::writeBoolean(onGround, array);
    return array;
}

std::string PacketEntityMove::toString() const {
    return std::string("PacketEntityMove{eid=") + std::to_string(eid) + ",...}";
}
