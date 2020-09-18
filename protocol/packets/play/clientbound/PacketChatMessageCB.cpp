//
// Created by thekinrar on 18/09/2020.
//

#include "PacketChatMessageCB.h"

PacketChatMessageCB::PacketChatMessageCB(const std::string &message) : message(message) {}

std::vector<std::byte> PacketChatMessageCB::bytes() {
    std::string json(R"({"text":")");
    json += message;
    json += "\"}";

    std::vector<std::byte> array;
    PacketData::writeVarInt(0x0E, array);
    PacketData::writeString(json, array);
    PacketData::writeByte(0, array);
    PacketData::writeLong(0, array);
    PacketData::writeLong(0, array);
    return array;
}

std::string PacketChatMessageCB::toString() const {
    return std::string("PacketChatMessageSB{") + message + "}";
}
