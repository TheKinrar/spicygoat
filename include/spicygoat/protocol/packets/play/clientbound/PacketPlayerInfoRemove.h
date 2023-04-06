//
// Created by thekinrar on 25/12/22.
//

#ifndef SPICYGOAT_PACKETPLAYERINFOREMOVE_H
#define SPICYGOAT_PACKETPLAYERINFOREMOVE_H

#include <forward_list>

#include <spicygoat/protocol/ClientBoundPacket.h>

class PacketPlayerInfoRemove : public ClientBoundPacket {
   public:
    explicit PacketPlayerInfoRemove(const std::forward_list<uuids::uuid> &uuids) : uuids(uuids) {}

    [[nodiscard]] std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;
        PacketData::writeVarInt(0x35, array);

        PacketData::writeVarInt(std::distance(uuids.begin(), uuids.end()), array);
        for(auto uuid : uuids) {
            PacketData::writeUuid(uuid, array);
        }

        return array;
    }

    [[nodiscard]] std::string toString() const override {
        return std::string("PacketPlayerInfoRemove{count=") +
               std::to_string(std::distance(uuids.begin(), uuids.end())) + ",...}";
    }

    const std::forward_list<uuids::uuid> uuids;
};

#endif  // SPICYGOAT_PACKETPLAYERINFOREMOVE_H
