//
// Created by thekinrar on 15/01/23.
//

#pragma once

#include <spicygoat/protocol/ClientBoundPacket.h>
#include <spicygoat/tags/Tag.h>

class PacketUpdateTags : public ClientBoundPacket {
    std::map<std::string, std::vector<std::reference_wrapper<Tag>>> tags;

   public:
    explicit PacketUpdateTags(const std::map<std::string, std::vector<std::reference_wrapper<Tag>>>& tags)
        : ClientBoundPacket(Packets::C_UPDATE_TAGS), tags(tags) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        std::vector<std::byte> array;
        PacketData::writeVarInt(tags.size(), array);
        for(const auto& tagType : tags) {
            PacketData::writeString(tagType.first, array);
            PacketData::writeVarInt(tagType.second.size(), array);
            for(const auto& tag : tagType.second) {
                PacketData::writeString(tag.get().getName(), array);
                PacketData::writeVarInt(tag.get().getTargets().size(), array);
                for(const auto& item : tag.get().getTargets()) {
                    PacketData::writeVarInt(item, array);
                }
            }
        }

        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketUpdateTags{}";
    }
};
