//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETPLAYERABILITIES_H
#define SPICYGOAT_PACKETPLAYERABILITIES_H

#include "../../ClientBoundPacket.h"

class PacketPlayerAbilities : public ClientBoundPacket {
   public:
    PacketPlayerAbilities(bool invulnerable, bool flying, bool allowFlying, bool creative, float flyingSpeed,
                          float fovModifier);

    std::vector<std::byte> bytes() const override;

    std::string toString() const override;

   private:
    bool invulnerable;
    bool flying;
    bool allowFlying;
    bool creative;

    float flyingSpeed;
    float fovModifier;
};

#endif  // SPICYGOAT_PACKETPLAYERABILITIES_H
