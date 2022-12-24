//
// Created by thekinrar on 01/09/2019.
//

#ifndef SPICYGOAT_PACKETPLAYERDIGGING_H
#define SPICYGOAT_PACKETPLAYERDIGGING_H


#include "../../ServerBoundPacket.h"

class PacketPlayerDigging : public ServerBoundPacket {
public:
    explicit PacketPlayerDigging(PacketData* data);

    std::string toString() const override;

    enum class Status {
        STARTED_DIGGING = 0,
        CANCELLED_DIGGING = 1,
        FINISHED_DIGGING = 2,
        DROP_ITEM_STACK = 3,
        DROP_ITEM = 4,
        USE_ITEM = 5,
        SWAP_ITEMS = 6
    };

    const Status status;
    const Position position;
    const uint8_t face;
    const int sequence;
};


#endif //SPICYGOAT_PACKETPLAYERDIGGING_H
