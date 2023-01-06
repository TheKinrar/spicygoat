//
// Created by thekinrar on 02/04/19.
//

#include "PacketChunkData.h"

#include <tag_array.h>

#include <iostream>

PacketChunkData::PacketChunkData(ChunkColumn &chunkColumn) : chunkColumn(chunkColumn) {}

std::vector<std::byte> PacketChunkData::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x20, array);
    PacketData::writeInt(chunkColumn.getX(), array);
    PacketData::writeInt(chunkColumn.getZ(), array);

    chunkColumn.writeHeightMapsToByteArray(array);

    std::vector<std::byte> data;
    chunkColumn.writeDataToByteArray(data);

    PacketData::writeVarInt(data.size(), array);
    PacketData::writeByteArray(data, array);

    PacketData::writeVarInt(0, array);  // TODO: block entities

    chunkColumn.writeLightToByteArray(array);

    return array;
}

std::string PacketChunkData::toString() const {
    return std::string("PacketChunkData{") + std::to_string(chunkColumn.getX()) + "," +
           std::to_string(chunkColumn.getZ()) + "}";
}
