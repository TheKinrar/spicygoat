//
// Created by thekinrar on 07/01/23.
//

#pragma once

#include <spicygoat/protocol/ClientBoundPacket.h>
#include <spicygoat/util/math.h>
#include <spicygoat/world/geo/Location.h>

class PacketSpawnEntity : public ClientBoundPacket {
    int eid;
    uuids::uuid uuid;
    int type;
    Location loc;
    int data;
    int16_t velX, velY, velZ;

   public:
    PacketSpawnEntity(int eid, const uuids::uuid& uuid, int type, const Location& loc, int data, Vector3d vel)
        : ClientBoundPacket(Packets::C_SPAWN_ENTITY),
          eid(eid),
          uuid(uuid),
          type(type),
          loc(loc),
          data(data),
          velX((int16_t) (math::clamp(vel.getX(), -3.9, 3.9) * 8000)),
          velY((int16_t) (math::clamp(vel.getY(), -3.9, 3.9) * 8000)),
          velZ((int16_t) (math::clamp(vel.getZ(), -3.9, 3.9) * 8000)) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;
        PacketData::writeVarInt(eid, array);
        PacketData::writeUuid(uuid, array);
        PacketData::writeVarInt(type, array);
        PacketData::writeDouble(loc.getX(), array);
        PacketData::writeDouble(loc.getY(), array);
        PacketData::writeDouble(loc.getZ(), array);
        PacketData::writeAngle(loc.getPitch(), array);
        PacketData::writeAngle(loc.getYaw(), array);
        PacketData::writeAngle(loc.getYaw(), array); // head yaw
        PacketData::writeVarInt(data, array);
        PacketData::writeShort(velX, array);
        PacketData::writeShort(velY, array);
        PacketData::writeShort(velZ, array);
        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketSpawnEntity{}";
    }
};
