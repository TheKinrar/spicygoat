//
// Created by thekinrar on 16/05/23.
//

#pragma once

#include "../../../ClientBoundPacket.h"

class PacketExplosion : public ClientBoundPacket {
    double x, y, z;
    float strength;
    std::vector<Position> blocks;
    float velX, velY, velZ;

   public:
    PacketExplosion(double x, double y, double z, float strength, const std::vector<Position>& blocks,
                    float velX, float velY, float velZ)
        : ClientBoundPacket(Packets::C_EXPLOSION), x(x), y(y), z(z), strength(strength), blocks(blocks),
          velX(velX), velY(velY), velZ(velZ) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;
        PacketData::writeDouble(x, array);
        PacketData::writeDouble(y, array);
        PacketData::writeDouble(z, array);
        PacketData::writeFloat(strength, array);
        PacketData::writeVarInt(blocks.size(), array);
        for(const auto& block : blocks) {
            int dx = block.getX() - (int) std::floor(x);
            int dy = block.getY() - (int) std::floor(y);
            int dz = block.getZ() - (int) std::floor(z);

            if(dx < -128 || dx > 127 || dy < -128 || dy > 127 || dz < -128 || dz > 127)
                throw std::runtime_error("Block is too far away from explosion center");

            PacketData::writeByte((int8_t) dx, array);
            PacketData::writeByte((int8_t) dy, array);
            PacketData::writeByte((int8_t) dz, array);
        }
        PacketData::writeFloat(velX, array);
        PacketData::writeFloat(velY, array);
        PacketData::writeFloat(velZ, array);
        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketExplosion{}";
    }
};
