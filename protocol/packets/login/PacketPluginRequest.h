//
// Created by thekinrar on 25/12/22.
//

#ifndef SPICYGOAT_PACKETPLUGINREQUEST_H
#define SPICYGOAT_PACKETPLUGINREQUEST_H


#include <utility>

#include "../ClientBoundPacket.h"

class PacketPluginRequest : public ClientBoundPacket {
public:
    PacketPluginRequest(const int id, std::string channel, const std::vector<std::byte> &data) : id(id),
                                                                                                        channel(std::move(channel)),
                                                                                                        data(data) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() override {
        std::vector<std::byte> array;
        PacketData::writeVarInt(0x04, array);
        PacketData::writeVarInt(id, array);
        PacketData::writeString(channel, array);
        PacketData::writeByteArray(data, array);
        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return std::string("PacketPluginMessageCB{channel=") + channel + "}";
    }

    const int id;
    const std::string channel;
    const std::vector<std::byte> data;
};


#endif //SPICYGOAT_PACKETPLUGINREQUEST_H
