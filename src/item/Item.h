//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include <string>
#include <utility>

#include "../entities/EntityPlayer.h"
#include "../protocol/packets/play/serverbound/PacketUseItemOn.h"

class Item {
    std::string name;

   public:
    explicit Item(std::string  name) : name(std::move(name)) {}

    [[nodiscard]] const std::string& getName() const {
        return name;
    }

    virtual void onUseOn(EntityPlayer& player, const PacketUseItemOn &packet) const {};
};
