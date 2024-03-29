//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include <spicygoat/protocol/ClientBoundPacket.h>

#include <utility>

class PacketSetInventoryContent : public ClientBoundPacket {
    uint8_t windowId;
    int version;
    std::vector<ItemStack> stacks;
    ItemStack carried;

   public:
    PacketSetInventoryContent(uint8_t windowId, int version, const std::vector<ItemStack>& stacks, ItemStack carried)
        : ClientBoundPacket(Packets::C_SET_INVENTORY_CONTENT),
          windowId(windowId),
          version(version),
          stacks(stacks),
          carried(std::move(carried)) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;

        PacketData::writeUnsignedByte(windowId, array);
        PacketData::writeVarInt(version, array);
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
