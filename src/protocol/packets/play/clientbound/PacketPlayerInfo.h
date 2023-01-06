//
// Created by thekinrar on 07/05/19.
//

#ifndef SPICYGOAT_PACKETPLAYERINFO_H
#define SPICYGOAT_PACKETPLAYERINFO_H

#include <forward_list>

#include "../../../../entities/EntityPlayer.h"
#include "../../ClientBoundPacket.h"

class PacketPlayerInfo : public ClientBoundPacket {
   public:
    enum Action { AddPlayer = 0, UpdateGamemode = 1, UpdateLatency = 2, UpdateDisplayName = 3, RemovePlayer = 4 };

    PacketPlayerInfo(Action action, std::vector<std::shared_ptr<EntityPlayer>> &);

    std::vector<std::byte> bytes() const override;

    std::string toString() const override;

   private:
    Action action;
    std::vector<std::shared_ptr<EntityPlayer>> &players;
};

#endif  // SPICYGOAT_PACKETPLAYERINFO_H
