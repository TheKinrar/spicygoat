//
// Created by thekinrar on 06/01/23.
//

#include "PlayerData.h"

#include "../Server.h"

PlayerInventory PlayerData::getInventory(EntityPlayer& player) const {
    PlayerInventory ret(player);
    ret.setSyncEnabled(false);

    if(nbt->has_key("Inventory")) {
        auto inv = nbt->at("Inventory").as<nbt::tag_list>();
        for(const auto& e : inv) {
            auto& item = e.as<nbt::tag_compound>();
            if(item.has_key("tag")) {
                ret.setSlot(dataSlotToNetwork(item.at("Slot").as<nbt::tag_byte>()),
                            ItemStack(Server::get().getItemRegistry().keyToId.at(item.at("id").as<nbt::tag_string>()),
                                      item.at("Count").as<nbt::tag_byte>(),
                                      std::make_unique<nbt::tag_compound>(item.at("tag").as<nbt::tag_compound>())));
            } else {
                ret.setSlot(dataSlotToNetwork(item.at("Slot").as<nbt::tag_byte>()),
                            ItemStack(Server::get().getItemRegistry().keyToId.at(item.at("id").as<nbt::tag_string>())));
            }
        }
    }

    ret.setSyncEnabled(true);
    return ret;
}

void PlayerData::setInventory(const PlayerInventory& source) {
    nbt::tag_list inv;
    for(int8_t i = 0; i < PLAYER_INVENTORY_SIZE; ++i) {
        auto sourceItem = source.getSlot(i);

        if(sourceItem.present) {
            nbt::tag_compound item;
            item.insert("Slot", nbt::tag_byte(networkSlotToData(i)));
            item.insert("id", nbt::tag_string(Server::get().getItemRegistry().idToKey.at(sourceItem.id)));
            item.insert("Count", nbt::tag_byte(sourceItem.count));

            if(sourceItem.hasNbt) {
                item.insert("tag", nbt::tag_compound(*sourceItem.nbt));
            }

            inv.push_back(std::move(item));
        }
    }
    nbt->put("Inventory", std::move(inv));
}

PlayerAbilities PlayerData::getAbilities() const {
    if(nbt->has_key("abilities")) {
        auto& data = nbt->at("abilities").as<nbt::tag_compound>();
        return {
            static_cast<bool>(data.at("invulnerable").as<nbt::tag_byte>()),
            static_cast<bool>(data.at("flying").as<nbt::tag_byte>()),
            static_cast<bool>(data.at("mayfly").as<nbt::tag_byte>()),
            static_cast<bool>(data.at("instabuild").as<nbt::tag_byte>()),
            data.at("flySpeed").as<nbt::tag_float>(),
            data.at("walkSpeed").as<nbt::tag_float>(),
        };
    } else {
        return {};
    }
}

void PlayerData::setAbilities(const PlayerAbilities& source) {
    nbt::tag_compound data;
    data.insert("invulnerable", nbt::tag_byte(source.invulnerable));
    data.insert("flying", nbt::tag_byte(source.flying));
    data.insert("mayfly", nbt::tag_byte(source.allowFlying));
    data.insert("instabuild", nbt::tag_byte(source.creative));
    data.insert("flySpeed", nbt::tag_float(source.flySpeed));
    data.insert("walkSpeed", nbt::tag_float(source.walkSpeed));
    nbt->put("abilities", std::move(data));
}

GameMode::GameMode PlayerData::getGameMode(GameMode::GameMode def) const {
    if(nbt->has_key("playerGameType")) {
        return static_cast<GameMode::GameMode>(nbt->at("playerGameType").as<nbt::tag_int>().get());
    } else {
        return def;
    }
}

void PlayerData::setGameMode(const GameMode::GameMode& source) {
    nbt->put("playerGameType", nbt::tag_int((int) source));
}
