//
// Created by thekinrar on 19/09/2020.
//

#ifndef SPICYGOAT_PACKETSPAWNPLAYER_H
#define SPICYGOAT_PACKETSPAWNPLAYER_H


#include <libstud/uuid.hxx>

#include "../../ClientBoundPacket.h"

class PacketSpawnPlayer : public ClientBoundPacket {
public:
    explicit PacketSpawnPlayer(const int32_t eid, stud::uuid uuid, const double x, const double y, const double z,
                      const float yaw, const float pitch);

    std::vector<std::byte> bytes() override;

    std::string toString() const override;

    const int32_t eid;
    const stud::uuid uuid;
    const double x, y, z;
    const float yaw, pitch;
};


#endif //SPICYGOAT_PACKETSPAWNPLAYER_H
