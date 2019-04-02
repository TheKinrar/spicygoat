//
// Created by thekinrar on 02/04/19.
//

#include "PacketChunkData.h"

PacketChunkData::PacketChunkData(ChunkColumn &chunkColumn) : chunkColumn(chunkColumn) {}

std::vector<std::byte> PacketChunkData::bytes() {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x22, array);
    PacketData::writeInt(chunkColumn.getX(), array);
    PacketData::writeInt(chunkColumn.getZ(), array);
    PacketData::writeBoolean(true, array); // TODO: full chunk

    int16_t mask = 0;
    std::vector<std::byte> data;

    for(int y = 0; y < 16; ++y) {
        Chunk *chunk = chunkColumn.getChunk(y);

        if(chunk == nullptr)
            continue;

        mask |= (1 << y);

        PacketData::writeUnsignedByte(8, data); // TODO: bits per block (compression)
        PacketData::writeVarInt(2, data); // TODO: palette length
        PacketData::writeVarInt(0, data); // air
        PacketData::writeVarInt(1, data); // stone

        std::vector<std::byte> chunkData;

        for(int by = 0; by < 16; ++by) {
            for(int bz = 0; bz < 16; ++bz) {
                for(int bx = 0; bx < 16; ++bx) {
                    chunkData.push_back(std::byte(by == 0 ? 1 : 0));
                }
            }
        }

        while(chunkData.size() % 8 != 0)
            chunkData.push_back(std::byte());

        PacketD
    }

    PacketData::writeVarInt(mask, array);
    PacketData::writeVarInt(data.size(), array);
    PacketData::writeByteArray(data, array);

    for(int i = 0; i < 256; ++i) {
        PacketData::writeInt(127, array); // TODO: biomes
    }

    PacketData::writeVarInt(0, array); // TODO: block entities
    return array;
}
