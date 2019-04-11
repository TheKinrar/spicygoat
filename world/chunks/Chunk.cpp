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
    palette = ChunkPalette::fromNBT(nbt.at("Palette").as<nbt::tag_list>());
    blockStates = nbt.at("BlockStates").as<nbt::tag_long_array>().get();

    blockLight = nbt.at("BlockLight").as<nbt::tag_byte_array>().get();

    if(nbt.has_key("SkyLight"))
        skyLight = nbt.at("SkyLight").as<nbt::tag_byte_array>().get();

    if(getX() == -1 && getZ() == 0) {
        std::cout << "CHUNK y=" << getY() << std::endl;
        std::cout << palette->toString(true) << std::endl;
    }
}

ChunkPalette *Chunk::getPalette() const {
    return palette;
}

bool Chunk::hasData() {
    return palette != nullptr;// && palette->getBitsPerBlock() == 4;
}

void Chunk::writeToByteArray(std::vector<std::byte> &array) {
    palette->writeToByteArray(array);

    std::vector<std::byte> data;
    for(auto l : blockStates) {
        PacketData::writeUnsignedLong(l, data);
    }
    PacketData::writeVarInt(data.size() / 8, array);
    PacketData::writeByteArray(data, array);

    std::cout << "expected " << palette->getBitsPerBlock() * 512 << ", got " << data.size() << std::endl;

    for(int i = 0; i < 2048; ++i) {
        array.push_back(std::byte(blockLight[i]));
    }

    for(int i = 0; i < 2048; ++i) {
        array.push_back(std::byte(skyLight[i]));
    }
}
