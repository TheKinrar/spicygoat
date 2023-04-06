//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_PACKETJOINGAME_H
#define SPICYGOAT_PACKETJOINGAME_H

#include <spicygoat/entities/types/EntityPlayer.h>
#include <spicygoat/protocol/ClientBoundPacket.h>

class PacketJoinGame : public ClientBoundPacket {
   public:
    explicit PacketJoinGame(std::shared_ptr<EntityPlayer> player);

    std::vector<std::byte> bytes() const override;

    std::string toString() const override;

   private:
    std::shared_ptr<EntityPlayer> player;
};

#endif  // SPICYGOAT_PACKETJOINGAME_H
