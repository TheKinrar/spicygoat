//
// Created by thekinrar on 04/04/19.
//

#include <spicygoat/protocol/packets/play/clientbound/PacketUnloadChunk.h>

PacketUnloadChunk::PacketUnloadChunk(ChunkColumn &chunkColumn)
    : ClientBoundPacket(Packets::C_UNLOAD_CHUNK), column(chunkColumn) {}

std::vector<std::byte> PacketUnloadChunk::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeInt(column.getX(), array);
    PacketData::writeInt(column.getZ(), array);
    return array;
}

std::string PacketUnloadChunk::toString() const {
    return std::string("PacketUnloadChunk{") + column.toString() + "}";
}
