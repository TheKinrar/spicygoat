//
// Created by thekinrar on 04/04/19.
//

#include "PacketUnloadChunk.h"

PacketUnloadChunk::PacketUnloadChunk(ChunkColumn &chunkColumn) : column(chunkColumn) {

}

std::vector<std::byte> PacketUnloadChunk::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x1E, array);
    PacketData::writeInt(column.getX(), array);
    PacketData::writeInt(column.getZ(), array);
    return array;
}

std::string PacketUnloadChunk::toString() const {
    return std::string("PacketUnloadChunk{") + column.toString() + "}";
}
