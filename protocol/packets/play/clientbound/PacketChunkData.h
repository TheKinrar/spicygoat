//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETCHUNKDATA_H
#define SPICYGOAT_PACKETCHUNKDATA_H


#include "../../../../world/chunks/ChunkColumn.h"
#include "../../ClientBoundPacket.h"

class PacketChunkData : public ClientBoundPacket {
public:
    explicit PacketChunkData(ChunkColumn& chunkColumn);

    std::vector<std::byte> bytes() override;

    std::string toString() const override;

private:
    ChunkColumn& chunkColumn;
};


#endif//SPICYGOAT_PACKETCHUNKDATA_H
