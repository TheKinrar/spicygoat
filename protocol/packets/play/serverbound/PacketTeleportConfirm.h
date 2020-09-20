//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETTELEPORTCONFIRM_H
#define SPICYGOAT_PACKETTELEPORTCONFIRM_H


#include "../../ServerBoundPacket.h"

class PacketTeleportConfirm : public ServerBoundPacket {
public:
    PacketTeleportConfirm(PacketData *data);

    std::string toString() const override;

    int tpId;
};


#endif //SPICYGOAT_PACKETTELEPORTCONFIRM_H
