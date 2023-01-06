//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include "../../ServerBoundPacket.h"

class PacketSetHeldItem : public ServerBoundPacket {
    int16_t slot;

   public:
    explicit PacketSetHeldItem(PacketData& data)
        : ServerBoundPacket(Packets::S_SET_HELD_ITEM), slot(data.readShort()) {}

    int16_t getSlot() const {
        return slot;
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketSetHeldItem{}";
    }
};
