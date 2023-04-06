//
// Created by thekinrar on 07/01/23.
//

#pragma once

#include <memory>
#include <utility>
#include <vector>

#include <spicygoat/protocol/PacketData.h>

struct EntityMetadata {
    struct Entry {
        uint8_t index;

        explicit Entry(uint8_t index) : index(index) {}

        virtual void write(std::vector<std::byte>& vec) const {
            PacketData::writeUnsignedByte(index, vec);
        };
    };

    struct EntryItemStack : public Entry {
        ItemStack value;

        explicit EntryItemStack(uint8_t index, ItemStack value) : Entry(index), value(std::move(value)) {}

        void write(std::vector<std::byte>& vec) const override {
            Entry::write(vec);
            PacketData::writeVarInt(7, vec);
            PacketData::writeItemStack(value, vec);
        }
    };

    std::vector<std::unique_ptr<Entry>> entries;

    void add(std::unique_ptr<Entry> entry) {
        entries.push_back(std::move(entry));
    }

    void write(std::vector<std::byte>& vec) const {
        for(const auto& entry : entries) {
            entry->write(vec);
        }

        PacketData::writeUnsignedByte(0xFF, vec);
    }
};
