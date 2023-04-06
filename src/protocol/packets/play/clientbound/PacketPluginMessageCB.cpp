//
// Created by thekinrar on 01/04/19.
//

#include <spicygoat/protocol/packets/play/clientbound/PacketPluginMessageCB.h>

PacketPluginMessageCB::PacketPluginMessageCB(std::string channel, std::vector<std::byte> data) :
      ClientBoundPacket(Packets::C_PLUGIN_MESSAGE) {
    this->channel = channel;
    this->data = data;
}

std::vector<std::byte> PacketPluginMessageCB::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeString(channel, array);
    PacketData::writeByteArray(data, array);
    return array;
}

std::string PacketPluginMessageCB::toString() const {
    return std::string("PacketPluginMessageCB{channel=") + channel + "}";
}
