//
// Created by thekinrar on 02/04/19.
//

#include "Chunk.h"
#include "../../protocol/PacketData.h"
#include <tag_array.h>
#include <iostream>

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
    if(nbt.has_key("block_states")) {
        auto blockSection = nbt.at("block_states").as<nbt::tag_compound>();
        palette = ChunkPalette::fromNBT(blockSection.at("palette").as<nbt::tag_list>());
        if(blockSection.has_key("data")) {
            blockStates = blockSection.at("data").as<nbt::tag_long_array>().get();
        }
    }

    if (nbt.has_key("BlockLight"))
        blockLight = nbt.at("BlockLight").as<nbt::tag_byte_array>().get();

    if (nbt.has_key("SkyLight"))
        skyLight = nbt.at("SkyLight").as<nbt::tag_byte_array>().get();
}

[[nodiscard]]
const ChunkPalette& Chunk::getPalette() const {
    return *palette;
}

bool Chunk::hasData() {
    return palette != nullptr;
}

void Chunk::writeToByteArray(std::vector<std::byte> &array) {
    // non-air blocks
    if(palette->isSingle() && palette->getSingleBlockState().getName() == "minecraft:air") {
        // Palette only has air blocks, so that's an easy one.
        PacketData::writeShort(0, array);
    } else {
        // Send a fake value saying the chunk is full of blocks. This will not have a really significant performance
        // impact, but it should be fixed eventually.
        PacketData::writeShort(4096, array);
    }

    //std::cout << palette->toString(true) << std::endl; TODO
    palette->writeToByteArray(array);

    std::vector<std::byte> data;
    for(auto l : blockStates) {
        PacketData::writeUnsignedLong(l, data);
    }
    PacketData::writeVarInt(data.size() / 8, array);
    PacketData::writeByteArray(data, array);

    // TODO fake biomes
    PacketData::writeUnsignedByte(0, array); // single palette (0 b/entry)
    PacketData::writeVarInt(0, array); // biome ID 0 in global palette
    PacketData::writeVarInt(0, array); // no data (because single palette)
}
