//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include <string>
#include <utility>

#include <spicygoat/entities/types/EntityPlayer.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketUseItemOn.h>

class Item {
    std::string name;

   public:
    explicit Item(std::string name);
    Item(const Item&) = delete;

    [[nodiscard]] const std::string& getName() const {
        return name;
    }

    virtual void onUseOn(EntityPlayer& player, const PacketUseItemOn &packet) const {};
};
