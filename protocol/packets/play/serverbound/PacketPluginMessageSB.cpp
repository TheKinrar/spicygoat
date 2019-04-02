//
// Created by thekinrar on 02/04/19.
//

#include "PacketPluginMessageSB.h"

PacketPluginMessageSB::PacketPluginMessageSB(PacketData *data, TCPConnection *conn) : conn(conn) {
    channel = data->readString();
}

void PacketPluginMessageSB::handle() {
    // TODO
}

std::string PacketPluginMessageSB::toString() const {
    return std::string("PacketPluginMessageSB{channel=") + channel + ",unparsed}";
}
