//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_PACKETJOINGAME_H
#define SPICYGOAT_PACKETJOINGAME_H


#include "../../../../entities/EntityPlayer.h"
#include "../../ClientBoundPacket.h"

class PacketJoinGame : public ClientBoundPacket {
public:
    explicit PacketJoinGame(EntityPlayer *player);

    std::vector<std::byte> bytes() override;

    std::string toString() const override;

private:
    EntityPlayer *player;
};


#endif//SPICYGOAT_PACKETJOINGAME_H
