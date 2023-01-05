//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETCLIENTSETTINGS_H
#define SPICYGOAT_PACKETCLIENTSETTINGS_H


#include "../../ServerBoundPacket.h"

class PacketClientSettings : public ServerBoundPacket {
public:
    explicit PacketClientSettings(PacketData& data);

    std::string toString() const override;

    std::string locale;
    int8_t renderDistance;
    int chatMode;
    bool chatColors;
    uint8_t displayedSkinParts;
    int mainHand;
    bool textFiltering;
    bool serverListings;
};


#endif //SPICYGOAT_PACKETCLIENTSETTINGS_H
