//
// Created by thekinrar on 06/01/23.
//

#include "PlayerData.h"

#include "../Server.h"

PlayerInventory PlayerData::getInventory() const {
    PlayerInventory ret;

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
                            ItemStack(Server::get().getItemRegistry().keyToId.at(item.at("id").as<nbt::tag_string>()),
                                      item.at("Count").as<nbt::tag_byte>()));
            }
        }
    }

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
