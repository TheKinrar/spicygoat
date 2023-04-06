//
// Created by thekinrar on 18/09/2020.
//

#include <spicygoat/protocol/packets/play/clientbound/PacketChatMessageCB.h>

#include <nlohmann/json.hpp>

PacketChatMessageCB::PacketChatMessageCB(const std::string &message) : ClientBoundPacket(Packets::C_CHAT_MESSAGE),
      message(message) {}

std::vector<std::byte> PacketChatMessageCB::bytes() const {
    nlohmann::json j;
    j["text"] = message;

    std::vector<std::byte> array;
    PacketData::writeString(j.dump(), array);
    PacketData::writeBoolean(false, array);
    return array;
}

std::string PacketChatMessageCB::toString() const {
    return std::string("PacketChatMessageSB{") + message + "}";
}
