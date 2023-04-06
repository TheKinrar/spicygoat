//
// Created by thekinrar on 31/03/19.
//

#include <nlohmann/json.hpp>

#include <spicygoat/Server.h>
#include <spicygoat/protocol/packets/status/PacketResponse.h>

using json = nlohmann::json;

std::vector<std::byte> PacketResponse::bytes() const {
    json j;
    j["version"]["name"] = Protocol::PROTOCOL_VERSION_NAME;
    j["version"]["protocol"] = Protocol::PROTOCOL_VERSION_NUMBER;
    j["players"]["max"] = 20;
    j["players"]["online"] = Server::get().getPlayerCount();
    j["players"]["sample"] = json::array();
    j["description"]["text"] = "§e§lSpicyGoat - 1.19.3\n§r§cExperimental server";

    std::vector<std::byte> byteArray;
    PacketData::writeVarInt(0x00, byteArray);
    PacketData::writeString(j.dump(), byteArray);
    return byteArray;
}

std::string PacketResponse::toString() const {
    return std::string("PacketResponse{}");
}
