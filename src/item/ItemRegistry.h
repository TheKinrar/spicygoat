//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include "../util/Registry.h"
#include "Item.h"

class ItemRegistry : public Registry {
    std::unordered_map<int32_t, std::unique_ptr<Item>> items;

   public:
    explicit ItemRegistry() : Registry("minecraft:item") {}

    void add(std::unique_ptr<Item> item) {
        items.emplace(getId(item->getName()), std::move(item));
    }

    bool contains(int32_t id) const {
        return items.contains(id);
    }

    const Item& get(int32_t id) const {
        return *items.at(id);
    }

    void addMapping(const std::string& key, int32_t id) override;
};
