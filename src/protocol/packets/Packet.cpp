//
// Created by thekinrar on 30/03/19.
//

#include "Packet.h"

Packet::Packet(int id) : id(id) {}

int Packet::getId() const {
    return id;
}
