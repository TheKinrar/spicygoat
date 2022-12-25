//
// Created by thekinrar on 19/09/2020.
//

#include "PacketSpawnPlayer.h"

PacketSpawnPlayer::PacketSpawnPlayer(const int32_t eid, const uuid_t& uuid, const double x, const double y,
                                     const double z, const float yaw, const float pitch) : ClientBoundPacket(0x04),
                                                                                           eid(eid), uuid(uuid), x(x),
                                                                                           y(y), z(z), yaw(yaw),
                                                                                           pitch(pitch) {}

std::vector<std::byte> PacketSpawnPlayer::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x02, array);
    PacketData::writeVarInt(eid, array);
    PacketData::writeUuid(uuid, array);
    PacketData::writeDouble(x, array);
    PacketData::writeDouble(y, array);
    PacketData::writeDouble(z, array);
    PacketData::writeAngle(yaw, array);
    PacketData::writeAngle(pitch, array);
    return array;
}

std::string PacketSpawnPlayer::toString() const {
    return std::string("PacketSpawnPlayer{eid=") + std::to_string(eid) + "}";
}
