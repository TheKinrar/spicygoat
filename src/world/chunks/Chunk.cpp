//
// Created by thekinrar on 02/04/19.
//

#include "Chunk.h"

#include <tag_array.h>

#include <iostream>

#include "../../protocol/PacketData.h"

Chunk::Chunk(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {}

int32_t Chunk::getX() const {
    return x;
}

int32_t Chunk::getY() const {
    return y;
}

int32_t Chunk::getZ() const {
    return z;
}

void Chunk::loadNBT(nbt::tag_compound& nbt) {
    if(hasData()) throw std::runtime_error("Already loaded!");

    if(nbt.has_key("block_states")) {
        auto blockSection = nbt.at("block_states").as<nbt::tag_compound>();
        palette = ChunkPalette::fromNBT(blockSection.at("palette").as<nbt::tag_list>());
        if(blockSection.has_key("data")) {
            blockStates = blockSection.at("data").as<nbt::tag_long_array>().get();
        }
    }

    if(nbt.has_key("BlockLight")) {
        auto chars = nbt.at("BlockLight").as<nbt::tag_byte_array>().get();
        for(const auto& item : chars) blockLight.push_back(std::byte(item));
    }

    if(nbt.has_key("SkyLight")) {
        auto chars = nbt.at("SkyLight").as<nbt::tag_byte_array>().get();
        for(const auto& item : chars) skyLight.push_back(std::byte(item));
    }
}

[[nodiscard]] const ChunkPalette& Chunk::getPalette() const {
    return *palette;
}

bool Chunk::hasData() {
    return palette != nullptr;
}

void Chunk::writeDataToByteArray(std::vector<std::byte>& array) {
    PacketData::writeShort(4096 - countAirBlocks(), array);

    // std::cout << palette->toString(true) << std::endl; TODO
    palette->writeToByteArray(array);

    std::vector<std::byte> data;
    for(auto l : blockStates) {
        PacketData::writeUnsignedLong(l, data);
    }
    PacketData::writeVarInt(data.size() / 8, array);
    PacketData::writeByteArray(data, array);

    // TODO fake biomes
    PacketData::writeUnsignedByte(0, array);  // single palette (0 b/entry)
    PacketData::writeVarInt(0, array);        // biome ID 0 in global palette
    PacketData::writeVarInt(0, array);        // no data (because single palette)
}
