//
// Created by thekinrar on 07/01/23.
//

#pragma once

#include <utility>

#include "../../../../entities/EntityMetadata.h"
#include "../../ClientBoundPacket.h"

class PacketSetEntityMetadata : public ClientBoundPacket {
    int eid;
    EntityMetadata metadata;

   public:
    PacketSetEntityMetadata(int eid, EntityMetadata  metadata)
        : ClientBoundPacket(0x4E), eid(eid), metadata(std::move(metadata)) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;
        PacketData::writeVarInt(0x4E, array);
        PacketData::writeVarInt(eid, array);
        metadata.write(array);
        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketSetEntityMetadata{}";
    }
};
