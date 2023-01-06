//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include "../../ClientBoundPacket.h"

class PacketGameEvent : public ClientBoundPacket {
   public:
    enum Event {
        ChangeGamemode = 3,
    };

   private:
    Event event;
    float value;

   public:
    PacketGameEvent(Event event, float value) : ClientBoundPacket(0x1C), event(event), value(value) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;
        PacketData::writeVarInt(0x1C, array);
        PacketData::writeVarInt(event, array);
        PacketData::writeFloat(value, array);
        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketGameEvent{}";
    }
};
