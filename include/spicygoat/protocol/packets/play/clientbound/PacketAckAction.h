//
// Created by thekinrar on 22/01/23.
//

#pragma once

#include <spicygoat/protocol/ClientBoundPacket.h>

class PacketAckAction : public ClientBoundPacket {
   public:
    const int sequenceId;

    explicit PacketAckAction(int sequenceId) : ClientBoundPacket(Packets::C_ACK_ACTION), sequenceId(sequenceId) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;
        PacketData::writeVarInt(sequenceId, array);
        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketAckAction{}";
    }
};
