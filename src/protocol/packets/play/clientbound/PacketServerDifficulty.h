//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETSERVERDIFFICULTY_H
#define SPICYGOAT_PACKETSERVERDIFFICULTY_H

#include "../../ClientBoundPacket.h"

class PacketServerDifficulty : public ClientBoundPacket {
   public:
    explicit PacketServerDifficulty(uint8_t difficulty);

    std::vector<std::byte> bytes() const override;

    std::string toString() const override;

   private:
    uint8_t difficulty;
};

#endif  // SPICYGOAT_PACKETSERVERDIFFICULTY_H
