//
// Created by thekinrar on 01/04/19.
//

#include "ChannelMessage.h"

#include "../packets/play/clientbound/PacketPluginMessageCB.h"

ChannelMessage::ChannelMessage(const char* channel) {
    this->channel = std::string(channel);
}

void ChannelMessage::send(std::vector<std::byte> data, TCPConnection& conn) {
    conn.sendPacket(PacketPluginMessageCB(channel, data));
}
