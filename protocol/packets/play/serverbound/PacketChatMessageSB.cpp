//
// Created by thekinrar on 18/09/2020.
//

#include "PacketChatMessageSB.h"

PacketChatMessageSB::PacketChatMessageSB(PacketData* data) : ServerBoundPacket(Packets::S_CHAT_MESSAGE), message(data->readString()) {}

std::string PacketChatMessageSB::toString() const {
    return std::string("PacketChatMessageSB{") + message + "}";
}
