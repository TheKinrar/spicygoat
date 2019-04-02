//
// Created by thekinrar on 02/04/19.
//

#include "PacketClientSettings.h"

PacketClientSettings::PacketClientSettings(PacketData *data, TCPConnection *conn) : conn(conn) {
    locale = data->readString();
    renderDistance = data->readByte();
    chatMode = data->readVarInt();
    chatColors = data->readBoolean();
    displayedSkinParts = data->readUnsignedByte();
    mainHand = data->readVarInt();
}

void PacketClientSettings::handle() {
    // TODO
}

std::string PacketClientSettings::toString() const {
    return std::string("PacketClientSettings{locale=") + locale
            + ",render=" + std::to_string(renderDistance)
            + ",chatMode=" + std::to_string(chatMode)
            + ",chatColors=" + std::to_string(chatColors)
            + ",skin=" + std::to_string(displayedSkinParts)
            + ",hand=" + std::to_string(mainHand)
            + "}";
}
