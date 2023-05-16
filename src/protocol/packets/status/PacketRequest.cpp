//
// Created by thekinrar on 30/03/19.
//

#include <spicygoat/protocol/packets/status/PacketRequest.h>
#include <spicygoat/protocol/packets/status/PacketResponse.h>

PacketRequest::PacketRequest(PacketData&) : ServerBoundPacket(Packets::S_REQUEST) {}

std::string PacketRequest::toString() const {
    return std::string("PacketRequest{}");
}
