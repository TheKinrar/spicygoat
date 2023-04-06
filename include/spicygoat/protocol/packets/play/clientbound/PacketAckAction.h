//
// Created by thekinrar on 22/01/23.
//

#pragma once

#include <spicygoat/protocol/ClientBoundPacket.h>

class PacketAckAction : public ClientBoundPacket {
   public:
    const int sequenceId;

    explicit PacketAckAction(int sequenceId) : sequenceId(sequenceId) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;
        PacketData::writeVarInt(0x05, array);
        PacketData::writeVarInt(sequenceId, array);
        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketAckAction{}";
    }
};
