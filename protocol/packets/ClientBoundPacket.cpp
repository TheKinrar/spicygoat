//
// Created by thekinrar on 31/03/19.
//

#include "ClientBoundPacket.h"

ClientBoundPacket::ClientBoundPacket(int id) : Packet(id) {}

ClientBoundPacket::ClientBoundPacket() : Packet(-1) {}
