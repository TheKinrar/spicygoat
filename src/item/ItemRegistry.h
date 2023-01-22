//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include "../util/Registry.h"
#include "BlockItem.h"
#include "Item.h"

class ItemRegistry : public Registry {
    std::unordered_map<int32_t, std::unique_ptr<Item>> items;
    std::unordered_map<std::string, int32_t> blockItems;

   public:
    explicit ItemRegistry() : Registry("minecraft:item") {}

    void add(std::unique_ptr<Item> item) {
        items.emplace(getId(item->getName()), std::move(item));
    }

    void addBlockItem(std::unique_ptr<BlockItem> item) {
        blockItems.emplace(item->getBlock().getName().toString(), getId(item->getName()));
        add(std::move(item));
    }

    void addMapping(const std::string& key, int32_t id) override;

    bool contains(int32_t id) const {
        return items.contains(id);
    }

    const Item& get(int32_t id) const {
        return *items.at(id);
    }

    ItemStack getLoot(const std::shared_ptr<BlockState>& block) const;
};
