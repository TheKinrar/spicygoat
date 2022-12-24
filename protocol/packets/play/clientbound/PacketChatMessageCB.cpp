//
// Created by thekinrar on 18/09/2020.
//

#include <nlohmann/json.hpp>

#include "PacketChatMessageCB.h"

PacketChatMessageCB::PacketChatMessageCB(const std::string &message) : message(message) {}

std::vector<std::byte> PacketChatMessageCB::bytes() {
    nlohmann::json j;
    j["text"] = message;

    std::vector<std::byte> array;
    PacketData::writeVarInt(0x60, array);
    PacketData::writeString(j.dump(), array);
    PacketData::writeBoolean(false, array);
    return array;
}

std::string PacketChatMessageCB::toString() const {
    return std::string("PacketChatMessageSB{") + message + "}";
}
