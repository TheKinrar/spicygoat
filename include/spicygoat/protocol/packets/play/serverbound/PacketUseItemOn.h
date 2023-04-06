//
// Created by thekinrar on 04/01/23.
//

#ifndef SPICYGOAT_PACKETUSEITEMON_H
#define SPICYGOAT_PACKETUSEITEMON_H

#include <spicygoat/protocol/ServerBoundPacket.h>

class PacketUseItemOn : public ServerBoundPacket {
   public:
    int hand;
    Position position;
    Face face;
    float cursorX;
    float cursorY;
    float cursorZ;
    bool insideBlock;
    int sequence;

    explicit PacketUseItemOn(PacketData& data)
        : ServerBoundPacket(Packets::S_USE_ITEM_ON),
          hand(data.readVarInt()),
          position(data.readPosition()),
          face(data.readFace()),
          cursorX(data.readFloat()),
          cursorY(data.readFloat()),
          cursorZ(data.readFloat()),
          insideBlock(data.readBoolean()),
          sequence(data.readVarInt()) {}

    [[nodiscard]] std::string toString() const override {
        return "PacketUseItemOn{...}";
    }
};

#endif  // SPICYGOAT_PACKETUSEITEMON_H
