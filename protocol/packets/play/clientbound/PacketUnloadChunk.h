//
// Created by thekinrar on 04/04/19.
//

#ifndef SPICYGOAT_PACKETUNLOADCHUNK_H
#define SPICYGOAT_PACKETUNLOADCHUNK_H


#include "../../ClientBoundPacket.h"

class PacketUnloadChunk : public ClientBoundPacket {
public:
    explicit PacketUnloadChunk(ChunkColumn &chunkColumn);

    std::vector<std::byte> bytes() override;

    std::string toString() const override;

private:
    ChunkColumn &column;
};


#endif //SPICYGOAT_PACKETUNLOADCHUNK_H
