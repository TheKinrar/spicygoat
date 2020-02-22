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

            if(y > -1 && y < 16) {
                auto chunk = new Chunk(x, y, z);
                chunk->loadNBT(section);
                chunks[y] = chunk;
            }
        }
    }
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

    return mask;
}

void ChunkColumn::writeHeightMapsToByteArray(std::vector<std::byte> &array) {
    std::ostringstream stream;
    //nbt::io::stream_writer writer(stream);
    //writer.write_payload(this->level->at("Heightmaps"));
    //writer.write_type(nbt::tag_type::End);

    // TODO: figure out if we need so send all heightmaps or MOTION_BLOCKING only
    nbt::io::write_tag("", this->level->at("Heightmaps"), stream);

    //nbt::tag_compound c;
    //c["MOTION_BLOCKING"] = this->level->at("Heightmaps").as<nbt::tag_compound>().at("MOTION_BLOCKING");
    /*writer.write_type(nbt::tag_type::Compound);
    writer.write_payload(c);*/
//    writer.write_type(nbt::tag_type::End);
    //nbt::io::write_tag("", c, stream);

    stream.seekp(0, std::ios::end);
    int size = stream.tellp();
    stream.seekp(0, std::ios::beg);

    std::string std_str = stream.str();
    const char *str = std_str.c_str();
    std::vector<std::byte> bytes;
    bytes.reserve(size);
    for(int i = 0; i < size; ++i) {
        bytes.push_back(static_cast<std::byte>(str[i]));
    }

    PacketData::writeByteArray(bytes, array);
}

std::string ChunkColumn::toString() {
    return std::string("ChunkColumn{x=") + std::to_string(x) + ",z=" + std::to_string(z) + "}";
}

bool ChunkColumn::hasData() {
    return nbt != nullptr;
}
