//
// Created by thekinrar on 31/03/19.
//

#include "PacketResponse.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::vector<std::byte> PacketResponse::bytes() {
    json j;
    j["version"]["name"] = "1.14";
    j["version"]["protocol"] = 477;
    j["players"]["max"] = 1;
    j["players"]["online"] = 0;
    j["players"]["sample"] = json::array();
    j["description"]["text"] = "§e§lSpicyGoat - 1.14\n§r§cExperimental server";

    std::vector<std::byte> byteArray;
    PacketData::writeVarInt(0x00, byteArray);
    PacketData::writeString(j.dump(), byteArray);
    return byteArray;
}

std::string PacketResponse::toString() const {
    return std::string("PacketResponse{}");
}
