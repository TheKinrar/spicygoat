//
// Created by thekinrar on 25/12/22.
//

#ifndef SPICYGOAT_PACKETRENDERCENTER_H
#define SPICYGOAT_PACKETRENDERCENTER_H

#include <spicygoat/protocol/ClientBoundPacket.h>

class PacketRenderCenter : public ClientBoundPacket {
   public:
    explicit PacketRenderCenter(int x, int z) : ClientBoundPacket(Packets::C_RENDER_CENTER), x(x), z(z) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;
        PacketData::writeVarInt(x, array);
        PacketData::writeVarInt(z, array);
        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return std::string("PacketRenderCenter{x=") + std::to_string(x) + ",z=" + std::to_string(z) + "}";
    }

    const int x, z;
};

#endif  // SPICYGOAT_PACKETRENDERCENTER_H
