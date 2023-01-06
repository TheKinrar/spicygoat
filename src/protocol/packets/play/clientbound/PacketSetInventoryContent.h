//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include <utility>

#include "../../ClientBoundPacket.h"

class PacketSetInventoryContent : public ClientBoundPacket {
    uint8_t windowId;
    std::vector<ItemStack> stacks;
    ItemStack carried;

   public:
    PacketSetInventoryContent(uint8_t windowId, const std::vector<ItemStack>& stacks, ItemStack carried)
        : ClientBoundPacket(0x10), windowId(windowId), stacks(stacks), carried(std::move(carried)) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;

        PacketData::writeVarInt(0x10, array);
        PacketData::writeUnsignedByte(windowId, array);
        PacketData::writeVarInt(0, array); // TODO "State ID"???
        PacketData::writeVarInt(stacks.size(), array);
        for(const auto& item : stacks) {
            PacketData::writeItemStack(item, array);
        }
        PacketData::writeItemStack(carried, array);

        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketSetInventoryContent{}";
    }
};
