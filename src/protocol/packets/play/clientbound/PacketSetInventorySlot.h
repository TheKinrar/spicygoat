//
// Created by nicolas on 1/9/23.
//

#pragma once

#include <utility>

#include "../../ClientBoundPacket.h"

class PacketSetInventorySlot  : public ClientBoundPacket {
    int8_t windowId;
    int version;
    int16_t slot;
    ItemStack stack;

   public:
    PacketSetInventorySlot(int8_t windowId, int version, int16_t slot, ItemStack stack)
        : ClientBoundPacket(0x12), windowId(windowId), version(version), slot(slot), stack(std::move(stack)) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;

        PacketData::writeVarInt(0x12, array);
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
