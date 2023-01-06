//
// Created by thekinrar on 30/03/19.
//

#include "PacketRequest.h"

#include "PacketResponse.h"

PacketRequest::PacketRequest(PacketData&) : ServerBoundPacket(Packets::S_REQUEST) {}

std::string PacketRequest::toString() const {
    return std::string("PacketRequest{}");
}
