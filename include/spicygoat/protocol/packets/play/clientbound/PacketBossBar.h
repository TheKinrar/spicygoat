//
// Created by thekinrar on 15/03/23.
//

#pragma once

#include <spicygoat/bossbar/BossBar.h>

#include <spicygoat/protocol/ClientBoundPacket.h>

class PacketBossBar : public ClientBoundPacket {
   public:
    enum class Action {
        Add,
        Remove,
        UpdateHealth,
        UpdateTitle,
        UpdateStyle
    };

   private:
    BossBar& bar;
    Action action;

   public:
    PacketBossBar(BossBar& bar, Action action) : bar(bar), action(action) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() const override {
        nlohmann::json j;
        j["text"] = bar.getTitle();

        std::vector<std::byte> array;
        PacketData::writeVarInt(0x0A, array);
        PacketData::writeUuid(bar.getId(), array);
        PacketData::writeVarInt(static_cast<int>(action), array);
        switch(action) {
            case Action::Add:
                PacketData::writeString(j.dump(), array);
                PacketData::writeFloat(bar.getHealth(), array);
                PacketData::writeVarInt(static_cast<int>(bar.getColor()), array);
                PacketData::writeVarInt(static_cast<int>(bar.getDivision()), array);
                PacketData::writeUnsignedByte(0, array); // Flags
                break;
            case Action::Remove:
                break;
            case Action::UpdateHealth:
                PacketData::writeFloat(bar.getHealth(), array);
                break;
            case Action::UpdateTitle:
                PacketData::writeString(j.dump(), array);
                break;
            case Action::UpdateStyle:
                PacketData::writeVarInt(static_cast<int>(bar.getColor()), array);
                PacketData::writeVarInt(static_cast<int>(bar.getDivision()), array);
                break;
        }
        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return "PacketBossBar{}";
    }
};
