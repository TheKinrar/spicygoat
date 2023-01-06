//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include "../../ServerBoundPacket.h"

class PacketChatCommand : public ServerBoundPacket {
    std::string message;

   public:
    explicit PacketChatCommand(PacketData& data)
        : ServerBoundPacket(Packets::S_CHAT_COMMAND), message(data.readString()) {
        data.readLong(); // Timestamp
        data.readLong(); // Salt
        int len = data.readVarInt();
        for(int i = 0; i < len; ++i) {
            data.readString(); // Arg name
            data.readPacketData(256); // Arg signature
        }
        data.readVarInt(); // message count
        std::bitset<20> ack;
        data.readVarInt(); // ack offset (huh?)
        data.readFixedBitSet(ack);
    }

    [[nodiscard]] const std::string& getMessage() const {
        return message;
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketChatCommand{}";
    }
};
