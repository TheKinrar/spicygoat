//
// Created by thekinrar on 06/04/23.
//

#pragma once

#include <spicygoat/protocol/ServerBoundPacket.h>

class PacketUseItem : public ServerBoundPacket {
   public:
    const int hand;
    const int sequence;

    explicit PacketUseItem(PacketData& data) : ServerBoundPacket(Packets::S_USE_ITEM),
          hand(data.readVarInt()),
          sequence(data.readVarInt()) {}

    [[nodiscard]] std::string toString() const override {
        return "PacketUseItem{}";
    }
};
