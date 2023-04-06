//
// Created by thekinrar on 01/04/19.
//

#include <spicygoat/protocol/packets/login/PacketLoginSuccess.h>

PacketLoginSuccess::PacketLoginSuccess(uuids::uuid uuid, const std::string &username) :
      ClientBoundPacket(Packets::C_LOGIN_SUCCESS) {
    this->uuid = uuid;
    this->username = username;
}

std::vector<std::byte> PacketLoginSuccess::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeUuid(uuid, array);
    PacketData::writeString(username, array);
    PacketData::writeVarInt(0, array);
    return array;
}

std::string PacketLoginSuccess::toString() const {
    return std::string("PacketLoginSuccess{uuid=") + to_string(uuid) + ",username=" + username + "}";
}
