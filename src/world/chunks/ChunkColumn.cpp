//
// Created by thekinrar on 02/04/19.
//

#include "ChunkColumn.h"

#include <tag_array.h>
#include <tag_list.h>
#include <tag_primitive.h>

#include <iostream>
#include <string>
#include <vector>

#include "../../protocol/PacketData.h"
#include "spdlog/spdlog.h"

ChunkColumn::ChunkColumn(int32_t x, int32_t z) : x(x), z(z) {
    for(auto &chunk : chunks) chunk = nullptr;
}

int32_t ChunkColumn::getX() const {
    return x;
}

int32_t ChunkColumn::getZ() const {
    return z;
}

Chunk &ChunkColumn::getChunk(int32_t y) {
    auto &ptr = chunks[y + 5];
    if(ptr)
        return *ptr;
    else {
        chunks[y + 5] = std::make_unique<Chunk>(x, y, z);
        return *chunks[y + 5];
    }
}

Position2D ChunkColumn::getPosition2D() {
    return Position2D(x, z);
}

void ChunkColumn::setNbt(std::unique_ptr<nbt::tag_compound> &nbt) {
    this->nbt = std::move(nbt);

    if(this->nbt->has_key("sections")) {
        for(auto &value : this->nbt->at("sections").as<nbt::tag_list>()) {
            if(value.get_type() == nbt::tag_type::Compound) {
                auto section = value.as<nbt::tag_compound>();
                int8_t y = section.at("Y").as<nbt::tag_byte>();

                if(y < -5 || y > 20) {
//                    std::cerr << "WARNING: chunk outside of boundaries! skipping " << x << ";" << (int)y << ";" << z
//                              << std::endl;
                } else {
                    //                    std::cerr << "Loading " << x << ";" << (int) y << ";" << z << std::endl;

                    getChunk(y).loadNBT(section);
                }
            }
        }
    }
}

void ChunkColumn::writeDataToByteArray(std::vector<std::byte> &array) {
    for(int8_t y = -4; y < 20; ++y) {
        auto &chunk = getChunk(y);

        if(!chunk.hasData()) {
            throw std::runtime_error("Missing chunk data");
        }

        chunk.writeDataToByteArray(array);
    }
}

void ChunkColumn::writeLightToByteArray(std::vector<std::byte> &array) {
    std::bitset<26> blockMask, skyMask;
    std::vector<std::byte> blockData, skyData;

    for(int8_t y = -5; y < 21; ++y) {
        auto &chunk = getChunk(y);

        if(chunk.hasBlockLightData()) {
            blockMask.set(y + 5);
            PacketData::writeVarInt(chunk.getBlockLightData().size(), blockData);
            PacketData::writeByteArray(chunk.getBlockLightData(), blockData);
        }

        if(chunk.hasSkyLightData()) {
            skyMask.set(y + 5);
            PacketData::writeVarInt(chunk.getSkyLightData().size(), skyData);
            PacketData::writeByteArray(chunk.getSkyLightData(), skyData);
        }
    }

    std::bitset<26> emptyBlockMask = blockMask;
    emptyBlockMask.flip();
    std::bitset<26> emptySkyMask = skyMask;
    emptySkyMask.flip();

    PacketData::writeBoolean(true, array);  // Trust edges

    PacketData::writeBitSet(skyMask, array);
    PacketData::writeBitSet(blockMask, array);
    PacketData::writeBitSet(skyMask, array);
    PacketData::writeBitSet(blockMask, array);

    PacketData::writeVarInt(skyMask.count(), array);
    PacketData::writeByteArray(skyData, array);
    PacketData::writeVarInt(blockMask.count(), array);
    PacketData::writeByteArray(blockData, array);
}

void ChunkColumn::writeHeightMapsToByteArray(std::vector<std::byte> &array) {
    std::ostringstream stream;
    // nbt::io::stream_writer writer(stream);
    // writer.write_payload(this->level->at("Heightmaps"));
    // writer.write_type(nbt::tag_type::End);

    // TODO: figure out if we need so send all heightmaps or MOTION_BLOCKING only
    nbt::io::write_tag("", this->nbt->at("Heightmaps"), stream);

    // nbt::tag_compound c;
    // c["MOTION_BLOCKING"] = this->level->at("Heightmaps").as<nbt::tag_compound>().at("MOTION_BLOCKING");
    /*writer.write_type(nbt::tag_type::Compound);
    writer.write_payload(c);*/
    //    writer.write_type(nbt::tag_type::End);
    // nbt::io::write_tag("", c, stream);

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
