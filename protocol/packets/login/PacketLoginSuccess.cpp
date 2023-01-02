//
// Created by thekinrar on 01/04/19.
//

#include "PacketLoginSuccess.h"

PacketLoginSuccess::PacketLoginSuccess(stud::uuid uuid, const std::string &username) {
    this->uuid = uuid;
    this->username = username;
}

std::vector<std::byte> PacketLoginSuccess::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x02, array);
    PacketData::writeUuid(uuid, array);
    PacketData::writeString(username, array);
    PacketData::writeVarInt(0, array);
    return array;
}

std::string PacketLoginSuccess::toString() const {
    return std::string("PacketLoginSuccess{uuid=") + uuid.string() + ",username=" + username + "}";
}
