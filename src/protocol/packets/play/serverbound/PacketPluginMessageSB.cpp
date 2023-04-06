//
// Created by thekinrar on 02/04/19.
//

#include <spicygoat/protocol/packets/play/serverbound/PacketPluginMessageSB.h>

PacketPluginMessageSB::PacketPluginMessageSB(PacketData& data) : ServerBoundPacket(Packets::S_PLUGIN_MESSAGE) {
    this->channel = data.readString();
    data.readByteArray(this->data, data.remaining());
}

std::string PacketPluginMessageSB::toString() const {
    return std::string("PacketPluginMessageSB{channel=") + channel + ",data=" + std::to_string(data.size()) + "B}";
}
