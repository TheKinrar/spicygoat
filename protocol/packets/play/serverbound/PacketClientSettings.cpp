//
// Created by thekinrar on 02/04/19.
//

#include "PacketClientSettings.h"

PacketClientSettings::PacketClientSettings(PacketData *data) : ServerBoundPacket(Packets::S_CLIENT_SETTINGS) {
    locale = data->readString();
    renderDistance = data->readByte();
    chatMode = data->readVarInt();
    chatColors = data->readBoolean();
    displayedSkinParts = data->readUnsignedByte();
    mainHand = data->readVarInt();
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
