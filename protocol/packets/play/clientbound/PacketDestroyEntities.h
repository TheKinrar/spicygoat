//
// Created by thekinrar on 19/09/2020.
//

#ifndef SPICYGOAT_PACKETDESTROYENTITIES_H
#define SPICYGOAT_PACKETDESTROYENTITIES_H


#include "../../ClientBoundPacket.h"

class PacketDestroyEntities : public ClientBoundPacket {
public:
    explicit PacketDestroyEntities(int32_t eid);

    std::vector<std::byte> bytes() override;

    std::string toString() const override;

private:
    int32_t eid;
};


#endif //SPICYGOAT_PACKETDESTROYENTITIES_H
