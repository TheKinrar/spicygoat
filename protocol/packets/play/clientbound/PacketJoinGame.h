//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_PACKETJOINGAME_H
#define SPICYGOAT_PACKETJOINGAME_H


#include "../../ClientBoundPacket.h"
#include "../../../../entities/EntityPlayer.h"

class PacketJoinGame : public ClientBoundPacket {
public:
    explicit PacketJoinGame(std::shared_ptr<EntityPlayer> player);

    std::vector<std::byte> bytes() const override;

    std::string toString() const override;

private:
    std::shared_ptr<EntityPlayer> player;
};


#endif //SPICYGOAT_PACKETJOINGAME_H
