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
    if(nbt.has_key("BlockStates")) {
        palette = ChunkPalette::fromNBT(nbt.at("Palette").as<nbt::tag_list>());
        blockStates = nbt.at("BlockStates").as<nbt::tag_long_array>().get();
    }

    if (nbt.has_key("BlockLight"))
        blockLight = nbt.at("BlockLight").as<nbt::tag_byte_array>().get();

    if (nbt.has_key("SkyLight"))
        skyLight = nbt.at("SkyLight").as<nbt::tag_byte_array>().get();
}

ChunkPalette *Chunk::getPalette() const {
    return palette;
}

bool Chunk::hasData() {
    return palette != nullptr;
}

void Chunk::writeToByteArray(std::vector<std::byte> &array) {
    PacketData::writeShort(4096, array);

    //std::cout << palette->toString(true) << std::endl; TODO
    palette->writeToByteArray(array);

    std::vector<std::byte> data;
    for(auto l : blockStates) {
        PacketData::writeUnsignedLong(l, data);
    }
    PacketData::writeVarInt(data.size() / 8, array);
    PacketData::writeByteArray(data, array);
}
