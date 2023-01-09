//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETPLAYERABILITIES_H
#define SPICYGOAT_PACKETPLAYERABILITIES_H

#include "../../../../util/PlayerAbilities.h"
#include "../../ClientBoundPacket.h"

class PacketPlayerAbilities : public ClientBoundPacket {
   public:
    PacketPlayerAbilities(PlayerAbilities value);

    std::vector<std::byte> bytes() const override;

    std::string toString() const override;

   private:
    PlayerAbilities value;
};

#endif  // SPICYGOAT_PACKETPLAYERABILITIES_H
