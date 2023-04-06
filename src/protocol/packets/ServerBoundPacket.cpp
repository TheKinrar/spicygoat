//
// Created by thekinrar on 31/03/19.
//

#include <spicygoat/protocol/ServerBoundPacket.h>

#include <stdexcept>

std::vector<std::byte> ServerBoundPacket::bytes() const {
    throw std::runtime_error("Called bytes() on server-bound packet");
}

ServerBoundPacket::ServerBoundPacket(int id) : Packet(id) {}
