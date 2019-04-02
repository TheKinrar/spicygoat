//
// Created by thekinrar on 31/03/19.
//

#include <stdexcept>
#include "ClientBoundPacket.h"

void ClientBoundPacket::handle() {
    throw std::runtime_error("Called handle() on client-bound packet");
}
