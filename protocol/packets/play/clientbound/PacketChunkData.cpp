//
// Created by thekinrar on 02/04/19.
//

#include <iostream>
#include <tag_array.h>
#include "PacketChunkData.h"

PacketChunkData::PacketChunkData(ChunkColumn &chunkColumn) : chunkColumn(chunkColumn) {}

std::vector<std::byte> PacketChunkData::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x20, array);
    PacketData::writeInt(chunkColumn.getX(), array);
    PacketData::writeInt(chunkColumn.getZ(), array);

    chunkColumn.writeHeightMapsToByteArray(array);

    std::vector<std::byte> data;
    chunkColumn.writeToByteArray(data);

    PacketData::writeVarInt(data.size(), array);
    PacketData::writeByteArray(data, array);

    PacketData::writeVarInt(0, array); // TODO: block entities

    PacketData::writeBoolean(true, array); // Trust edges

    // Dummy bitset for light data, assuming 24 chunks per column
    std::bitset<26> bitset;

    PacketData::writeBitSet(bitset, array); // sky light mask
    PacketData::writeBitSet(bitset, array); // block light mask
    PacketData::writeBitSet(bitset, array); // empty sky light mask
    PacketData::writeBitSet(bitset, array); // empty block light mask

    PacketData::writeVarInt(0, array); // no sky light
    PacketData::writeVarInt(0, array); // no block light

    return array;
}

std::string PacketChunkData::toString() const {
    return std::string("PacketChunkData{") + std::to_string(chunkColumn.getX()) + "," + std::to_string(chunkColumn.getZ()) + "}";
}
