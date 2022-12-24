//
// Created by thekinrar on 01/04/19.
//

#include "PacketPluginMessageCB.h"

PacketPluginMessageCB::PacketPluginMessageCB(std::string channel, std::vector<std::byte> data) {
    this->channel = channel;
    this->data = data;
}

std::vector<std::byte> PacketPluginMessageCB::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x15, array);
    PacketData::writeString(channel, array);
    PacketData::writeByteArray(data, array);
    return array;
}

std::string PacketPluginMessageCB::toString() const {
    return std::string("PacketPluginMessageCB{channel=") + channel + "}";
}
