//
// Created by thekinrar on 19/09/2020.
//

#include <spicygoat/protocol/packets/play/clientbound/PacketSpawnPlayer.h>

PacketSpawnPlayer::PacketSpawnPlayer(const int32_t eid, uuids::uuid uuid, const double x, const double y,
                                     const double z, const float yaw, const float pitch)
    : ClientBoundPacket(Packets::C_SPAWN_PLAYER), eid(eid), uuid(uuid), x(x), y(y), z(z), yaw(yaw), pitch(pitch) {}

std::vector<std::byte> PacketSpawnPlayer::bytes() const {
    std::vector<std::byte> array;
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
