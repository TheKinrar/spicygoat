//
// Created by thekinrar on 07/01/23.
//

#pragma once

#include <utility>

#include "../../protocol/packets/play/clientbound/PacketSpawnEntity.h"
#include "../Entity.h"

class EntityItem : public Entity {
    ItemStack stack;

   public:
    explicit EntityItem(ItemStack  stack) : stack(std::move(stack)) {}

    void tick() override;

    std::string getType() override {
        return "minecraft:item";
    }

    EntityMetadata toMetadata() override {
        EntityMetadata data;
        data.add(std::make_unique<EntityMetadata::EntryItemStack>(8, stack));
        return data;
    }
};
