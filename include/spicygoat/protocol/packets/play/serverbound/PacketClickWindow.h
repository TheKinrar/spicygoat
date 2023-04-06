//
// Created by thekinrar on 24/01/23.
//

#pragma once

#include <spicygoat/protocol/ServerBoundPacket.h>

struct PacketClickWindow : public ServerBoundPacket {
    enum class Mode {
        Normal,
        ShiftSwap,
        KeySwap,
        Middle,
        Drop,
        Drag,
        Double,
    };

    enum {
        LeftClick = 0,
        RightClick = 1,
        MiddleClick = 2,
        OffhandKey = 40,
    };

    uint8_t windowId;
    int stateId;
    int16_t slot;
    int8_t button;
    Mode mode;
    std::map<int16_t, ItemStack> stacks;
    ItemStack inHand;

    explicit PacketClickWindow(PacketData& data) : ServerBoundPacket(Packets::S_CLICK_WINDOW) {
        windowId = data.readUnsignedByte();
        stateId = data.readVarInt();
        slot = data.readShort();
        button = data.readByte();
        mode = static_cast<Mode>(data.readVarInt());
        int len = data.readVarInt();
        for(int i = 0; i < len; ++i) {
            auto slot = data.readShort();
            stacks.emplace(slot, data.readItemStack());
        }
        inHand = data.readItemStack();
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketClickWindow{}";
    }
};
