//
// Created by thekinrar on 07/01/23.
//

#pragma once

#include <utility>

#include "../../protocol/packets/play/clientbound/PacketSpawnEntity.h"
#include "../../util/Random.h"
#include "../Entity.h"

class EntityItem : public Entity {
    ItemStack stack;
    int pickupDelay = 40;

   public:
    explicit EntityItem(ItemStack stack) : stack(std::move(stack)) {
        setVelocity(Vector3d(Random::get().nextDouble() * 0.2 - 0.1, 0.2, Random::get().nextDouble() * 0.2 - 0.1));
    }

    void tick() override;

    std::string getType() override {
        return "minecraft:item";
    }

    [[nodiscard]]
    int getPickupDelay() const {
        return pickupDelay;
    }

    void setPickupDelay(int pickupDelay) {
        EntityItem::pickupDelay = pickupDelay;
    }

    EntityMetadata toMetadata() override {
        EntityMetadata data;
        data.add(std::make_unique<EntityMetadata::EntryItemStack>(8, stack));
        return data;
    }
};
