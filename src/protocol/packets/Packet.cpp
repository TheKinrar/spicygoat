//
// Created by thekinrar on 30/03/19.
//

#include <spicygoat/protocol/Packet.h>

Packet::Packet(int id) : id(id) {}

int Packet::getId() const {
    return id;
}
