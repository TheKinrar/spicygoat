//
// Created by nicolas on 1/9/23.
//

#pragma once

#include <spicygoat/protocol/ClientBoundPacket.h>

#include <utility>

class PacketSetInventorySlot : public ClientBoundPacket {
    int8_t windowId;
    int version;
    int16_t slot;
    ItemStack stack;

   public:
    PacketSetInventorySlot(int8_t windowId, int version, int16_t slot, ItemStack stack)
        : ClientBoundPacket(Packets::C_SET_INVENTORY_SLOT),
          windowId(windowId),
          version(version),
          slot(slot),
          stack(std::move(stack)) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;

        PacketData::writeByte(windowId, array);
        PacketData::writeVarInt(version, array);
        PacketData::writeShort(slot, array);
        PacketData::writeItemStack(stack, array);

        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketSetInventorySlot{}";
    }
};
