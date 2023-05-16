//
// Created by thekinrar on 07/01/23.
//

#pragma once

#include <spicygoat/entities/EntityMetadata.h>
#include <spicygoat/protocol/ClientBoundPacket.h>

#include <utility>

class PacketSetEntityMetadata : public ClientBoundPacket {
    int eid;
    EntityMetadata metadata;

   public:
    PacketSetEntityMetadata(int eid, EntityMetadata metadata)
        : ClientBoundPacket(Packets::C_SET_ENTITY_METADATA), eid(eid), metadata(std::move(metadata)) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;
        PacketData::writeVarInt(eid, array);
        metadata.write(array);
        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketSetEntityMetadata{}";
    }
};
