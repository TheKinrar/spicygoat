//
// Created by thekinrar on 02/04/19.
//

#include "PacketPluginMessageSB.h"

PacketPluginMessageSB::PacketPluginMessageSB(PacketData* data) : ServerBoundPacket(Packets::S_PLUGIN_MESSAGE) {
    channel = data->readString();
}

std::string PacketPluginMessageSB::toString() const {
    return std::string("PacketPluginMessageSB{channel=") + channel + ",unparsed}";
}
