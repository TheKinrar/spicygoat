//
// Created by thekinrar on 07/05/19.
//

#ifndef SPICYGOAT_PACKETENTITYMOVELOOK_H
#define SPICYGOAT_PACKETENTITYMOVELOOK_H


#include "../../ClientBoundPacket.h"
#include "../../../../world/geo/Location.h"

class PacketEntityMoveLook : public ClientBoundPacket {
public:
    PacketEntityMoveLook(int32_t eid, double dx, double dy, double dz, float yaw, float pitch, bool onGround);

    std::vector<std::byte> bytes() override;

    std::string toString() const override;

private:
    int32_t eid;
    double dx, dy, dz;
    float yaw, pitch;
    bool onGround;
};


#endif //SPICYGOAT_PACKETENTITYMOVELOOK_H
