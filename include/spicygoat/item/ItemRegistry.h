//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include <memory>
#include <utility>

#include <spicygoat/item/BlockItem.h>
#include <spicygoat/item/Item.h>
#include <spicygoat/util/Registry.h>

class ItemRegistry : public Registry {
    std::unordered_map<std::string, std::reference_wrapper<Item>> itemsByKey;
    std::unordered_map<std::string, std::reference_wrapper<Item>> blockItems;

   public:
    explicit ItemRegistry() : Registry("minecraft:item") {}

    void add(Item& item) {
        itemsByKey.emplace(item.getName(), item);
    }

    void addBlockItem(BlockItem& item) {
        blockItems.emplace(item.getBlock().getName().toString(), item);
    }

    const Item& get(int32_t id) const {
        return itemsByKey.at(getKey(id));
    }

    ItemStack getLoot(const std::shared_ptr<BlockState>& block) const;
};
