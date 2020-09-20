//
// Created by thekinrar on 01/04/19.
//

#include "PacketLoginSuccess.h"
#include <boost/uuid/uuid_io.hpp>

PacketLoginSuccess::PacketLoginSuccess(boost::uuids::uuid uuid, const std::string& username) {
    this->uuid = uuid;
    this->username = username;
}

std::vector<std::byte> PacketLoginSuccess::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x02, array);
    PacketData::writeUuid(uuid, array);
    PacketData::writeString(username, array);
    return array;
}

std::string PacketLoginSuccess::toString() const {
    return std::string("PacketLoginSuccess{uuid=") + boost::uuids::to_string(uuid) + ",username=" + username + "}";
}
