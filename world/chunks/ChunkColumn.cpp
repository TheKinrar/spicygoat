//
// Created by thekinrar on 02/04/19.
//

#include <string>
#include <vector>
#include <tag_array.h>
#include <tag_list.h>
#include <tag_primitive.h>
#include <iostream>
#include "ChunkColumn.h"
#include "../../protocol/PacketData.h"

ChunkColumn::ChunkColumn(int32_t x, int32_t z) : x(x), z(z) {
    for(auto & chunk : chunks)
        chunk = nullptr;
}

int32_t ChunkColumn::getX() const {
    return x;
}

int32_t ChunkColumn::getZ() const {
    return z;
}

Chunk *ChunkColumn::getChunk(int8_t y) {
    return chunks[y];
}

Position2D ChunkColumn::getPosition2D() {
    return Position2D(x, z);
}

void ChunkColumn::setNbt(std::unique_ptr<nbt::tag_compound> &nbt) {
    this->nbt = std::move(nbt);
    level = &this->nbt->at("Level").as<nbt::tag_compound>();

    if(level->has_key("Sections")) {
        for (auto &value : level->at("Sections").as<nbt::tag_list>()) {
            auto section = value.as<nbt::tag_compound>();
            int8_t y = section.at("Y").as<nbt::tag_byte>();

            Chunk *chunk = new Chunk(x, section.at("Y").as<nbt::tag_byte>(), z);
            chunk->loadNBT(section);
            chunks[y] = chunk;
        }

        std::cout << "Column " << x << ";" << z << " loaded with " << level->at("Sections").as<nbt::tag_list>().size() << " sections." << std::endl;
    } else {
        std::cout << "Column " << x << ";" << z << " loaded with no sections." << std::endl;
    }

    //std::cout << "=> " << level->at("xPos").as<nbt::tag_int>() << ";" << level->at("zPos").as<nbt::tag_int>() << std::endl;
}

uint16_t ChunkColumn::writeToByteArray(std::vector<std::byte> &array) {
    uint16_t mask = 0;

    for(uint y = 0; y < 16; ++y) {
        Chunk *chunk = getChunk(y);

        if(chunk == nullptr || !chunk->hasData())
            continue;

        mask |= (1u << y);

        chunk->writeToByteArray(array);
    }

    auto biomes = level->at("Biomes").as<nbt::tag_int_array>();
    for(int i = 0; i < 256; ++i) {
        PacketData::writeInt(biomes.at(i), array);
    }

    return mask;
}

std::string ChunkColumn::toString() {
    return std::string("ChunkColumn{x=") + std::to_string(x) + ",z=" + std::to_string(z) + "}";
}

bool ChunkColumn::hasData() {
    return nbt != nullptr;
}
