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
    auto &ptr = chunks[y + 4];
    if(ptr)
        return *ptr;
    else {
        ptr = std::make_unique<Chunk>(x, y, z);
        return *ptr;
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

                if(y < -4 || y > 19) {
                    std::cerr << "WARNING: chunk outside of boundaries! skipping " << x << ";" << (int)y << ";" << z
                              << std::endl;
                } else if(chunks[y + 4]) {
                    std::cerr << "WARNING: chunk already loaded! skipping " << x << ";" << (int)y << ";" << z
                              << std::endl;
                } else {
                    //                    std::cerr << "Loading " << x << ";" << (int) y << ";" << z << std::endl;

                    getChunk(y).loadNBT(section);
                }
            }
        }
    }
}

uint16_t ChunkColumn::writeToByteArray(std::vector<std::byte> &array) {
    uint16_t mask = 0;

    for(int8_t y = -4; y < 20; ++y) {
        auto &chunk = getChunk(y);

        if(!chunk.hasData()) {
            std::cerr << "WARNING: missing chunk data. client will not like this" << std::endl;
            continue;
        }

        mask |= (1u << y);

        chunk.writeToByteArray(array);
    }

    return mask;
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
