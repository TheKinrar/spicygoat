//
// Created by thekinrar on 01/09/2019.
//

#include <iostream>
#include "PacketPlayerDigging.h"

PacketPlayerDigging::PacketPlayerDigging(PacketData *data, TCPConnection *conn) : conn(conn), status(static_cast<Status>(data->readVarInt())), position(data->readPosition()) {}

void PacketPlayerDigging::handle() {
    if(status == Status::FINISHED_DIGGING) {
        std::cout << "finished digging" << std::endl;
    }
}

std::string PacketPlayerDigging::toString() const {
    return std::string("PacketPlayerDigging{status=") + std::to_string(static_cast<int>(status))
           + ",position=" + position.toString()
           + ",?}";
}
