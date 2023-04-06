//
// Created by thekinrar on 02/04/19.
//

#include <spicygoat/protocol/packets/play/serverbound/PacketTeleportConfirm.h>

PacketTeleportConfirm::PacketTeleportConfirm(PacketData& data) : ServerBoundPacket(Packets::S_TELEPORT_CONFIRM) {
    this->tpId = data.readVarInt();
}

std::string PacketTeleportConfirm::toString() const {
    return std::string("PacketTeleportConfirm{id=") + std::to_string(tpId) + "}";
}
