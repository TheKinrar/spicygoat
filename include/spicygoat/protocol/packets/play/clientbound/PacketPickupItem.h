//
// Created by nicolas on 1/9/23.
//

#pragma once

#include <spicygoat/protocol/ClientBoundPacket.h>

class PacketPickupItem : public ClientBoundPacket {
    int collected;
    int collector;
    int count;

   public:
    PacketPickupItem(int collected, int collector, int count)
        : ClientBoundPacket(0x63), collected(collected), collector(collector), count(count) {}


    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;

        PacketData::writeVarInt(0x63, array);
        PacketData::writeVarInt(collected, array);
        PacketData::writeVarInt(collector, array);
        PacketData::writeVarInt(count, array);

        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketPickupItem{}";
    }
};
