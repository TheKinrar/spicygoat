//
// Created by thekinrar on 02/04/19.
//

#include <spicygoat/protocol/packets/play/clientbound/PacketPlayerLocationCB.h>

PacketPlayerLocationCB::PacketPlayerLocationCB(Location location)
    : ClientBoundPacket(Packets::C_PLAYER_LOCATION), location(location) {}

std::vector<std::byte> PacketPlayerLocationCB::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeDouble(location.getX(), array);
    PacketData::writeDouble(location.getY(), array);
    PacketData::writeDouble(location.getZ(), array);
    PacketData::writeFloat(location.getYaw(), array);
    PacketData::writeFloat(location.getPitch(), array);
    PacketData::writeByte(0, array);      // TODO bitfield relative/absolute values (?)
    PacketData::writeVarInt(-42, array);  // TODO teleport ID
    return array;
}

std::string PacketPlayerLocationCB::toString() const {
    return std::string("PacketPlayerLocationCB{loc=") + location.toString() +
           ",id=" + std::to_string(-42)  // TODO teleport ID
           + "}";
}
