//
// Created by thekinrar on 31/03/19.
//

#include "PacketPing.h"

PacketPing::PacketPing(PacketData *data) : ServerBoundPacket(Packets::S_PING) {
    payload = data->readLong();
}

int64_t PacketPing::getPayload() const {
    return payload;
}

std::string PacketPing::toString() const {
    return std::string("PacketPing{payload=") + std::to_string(payload) + "}";
}
