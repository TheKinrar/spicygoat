//
// Created by thekinrar on 31/03/19.
//

#include <nlohmann/json.hpp>

#include <spicygoat/Server.h>
#include <spicygoat/protocol/packets/status/PacketResponse.h>

using json = nlohmann::json;

PacketResponse::PacketResponse() : ClientBoundPacket(Packets::S_RESPONSE) {}

std::vector<std::byte> PacketResponse::bytes() const {
    json j;
    j["version"]["name"] = Protocol::PROTOCOL_VERSION_NAME;
    j["version"]["protocol"] = Server::get().getProtocolVersionNumber();
    j["players"]["max"] = 20;
    j["players"]["online"] = Server::get().getPlayerCount();
    j["players"]["sample"] = json::array();
    j["description"]["text"] = std::string("§e§lSpicyGoat - ") + Protocol::PROTOCOL_VERSION_NAME + "\n§r§cExperimental server";

    std::vector<std::byte> byteArray;
    PacketData::writeString(j.dump(), byteArray);
    return byteArray;
}

std::string PacketResponse::toString() const {
    return std::string("PacketResponse{}");
}
