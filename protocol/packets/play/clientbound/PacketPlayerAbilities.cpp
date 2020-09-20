//
// Created by thekinrar on 02/04/19.
//

#include "PacketPlayerAbilities.h"

PacketPlayerAbilities::PacketPlayerAbilities(bool invulnerable, bool flying, bool allowFlying, bool creative,
                                             float flyingSpeed, float fovModifier) : invulnerable(invulnerable),
                                                                                     flying(flying),
                                                                                     allowFlying(allowFlying),
                                                                                     creative(creative),
                                                                                     flyingSpeed(flyingSpeed),
                                                                                     fovModifier(fovModifier) {}

std::vector<std::byte> PacketPlayerAbilities::bytes() {
    int8_t field = invulnerable | (flying << 1) | (allowFlying << 2) | (creative << 3);

    std::vector<std::byte> array;
    PacketData::writeVarInt(0x30, array);
    PacketData::writeByte(field, array);
    PacketData::writeFloat(flyingSpeed, array);
    PacketData::writeFloat(fovModifier, array);
    return array;
}

std::string PacketPlayerAbilities::toString() const {
    return std::string("PacketPlayerAbilities{inv=") + std::to_string(invulnerable)
           + ",fly=" + std::to_string(flying)
           + ",allowFly=" + std::to_string(allowFlying)
           + ",creative=" + std::to_string(creative)
           + ",flySpeed=" + std::to_string(flyingSpeed)
           + ",fovMod=" + std::to_string(fovModifier)
           + "}";
}
