//
// Created by thekinrar on 02/04/19.
//

#include "PacketPlayerAbilities.h"

PacketPlayerAbilities::PacketPlayerAbilities(PlayerAbilities value) : value(value) {}

std::vector<std::byte> PacketPlayerAbilities::bytes() const {
    int8_t field = value.invulnerable | (value.flying << 1) | (value.allowFlying << 2) | (value.creative << 3);

    std::vector<std::byte> array;
    PacketData::writeVarInt(0x30, array);
    PacketData::writeByte(field, array);
    PacketData::writeFloat(value.flySpeed, array);
    PacketData::writeFloat(value.walkSpeed, array);
    return array;
}

std::string PacketPlayerAbilities::toString() const {
    return std::string("PacketPlayerAbilities{inv=") + std::to_string(value.invulnerable) + ",fly=" + std::to_string(value.flying) +
           ",allowFly=" + std::to_string(value.allowFlying) + ",creative=" + std::to_string(value.creative) +
           ",flySpeed=" + std::to_string(value.flySpeed) + ",fovMod=" + std::to_string(value.walkSpeed) + "}";
}
