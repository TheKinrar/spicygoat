//
// Created by thekinrar on 01/09/2019.
//

#include "PacketPlayerDigging.h"

#include <iostream>

PacketPlayerDigging::PacketPlayerDigging(PacketData& data)
    : ServerBoundPacket(Packets::S_PLAYER_DIGGING),
      status(static_cast<Status>(data.readVarInt())),
      position(data.readPosition()),
      face(data.readByte()),
      sequence(data.readVarInt()) {}

std::string PacketPlayerDigging::toString() const {
    return std::string("PacketPlayerDigging{status=") + std::to_string(static_cast<int>(status)) +
           ",position=" + position.toString() + ",?}";
}
