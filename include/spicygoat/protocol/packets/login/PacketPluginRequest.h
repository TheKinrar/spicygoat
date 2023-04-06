//
// Created by thekinrar on 25/12/22.
//

#ifndef SPICYGOAT_PACKETPLUGINREQUEST_H
#define SPICYGOAT_PACKETPLUGINREQUEST_H

#include <utility>

#include <spicygoat/protocol/ClientBoundPacket.h>

class PacketPluginRequest : public ClientBoundPacket {
   public:
    PacketPluginRequest(const int id, std::string channel, const std::vector<std::byte> &data)
        : ClientBoundPacket(Packets::C_PLUGIN_REQUEST), id(id), channel(std::move(channel)), data(data) {}

    [[nodiscard]] std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;
        PacketData::writeVarInt(id, array);
        PacketData::writeString(channel, array);
        PacketData::writeByteArray(data, array);
        return array;
    }

    [[nodiscard]] std::string toString() const override {
        return std::string("PacketPluginMessageCB{channel=") + channel + "}";
    }

    const int id;
    const std::string channel;
    const std::vector<std::byte> data;
};

#endif  // SPICYGOAT_PACKETPLUGINREQUEST_H
