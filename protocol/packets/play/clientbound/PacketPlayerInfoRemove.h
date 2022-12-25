//
// Created by thekinrar on 25/12/22.
//

#ifndef SPICYGOAT_PACKETPLAYERINFOREMOVE_H
#define SPICYGOAT_PACKETPLAYERINFOREMOVE_H


#include <forward_list>
#include "../../ClientBoundPacket.h"

class PacketPlayerInfoRemove : public ClientBoundPacket {
public:
    explicit PacketPlayerInfoRemove(const std::forward_list<std::reference_wrapper<const uuid_t>> &uuids) : uuids(uuids) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() override {
        std::vector<std::byte> array;
        PacketData::writeVarInt(0x35, array);

        PacketData::writeVarInt(std::distance(uuids.begin(), uuids.end()), array);
        for(auto uuid : uuids) {
            PacketData::writeUuid(uuid.get(), array);
        }

        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return std::string("PacketPlayerInfoRemove{count=")
                + std::to_string(std::distance(uuids.begin(), uuids.end()))
               + ",...}";
    }

    const std::forward_list<std::reference_wrapper<const uuid_t>> uuids;
};


#endif //SPICYGOAT_PACKETPLAYERINFOREMOVE_H
