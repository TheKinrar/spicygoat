//
// Created by thekinrar on 12/03/23.
//

#pragma once

#include "../Entity.h"

class EntityFireball : public Entity {
   public:
    void tick() override;

    std::string getType() override {
        return "minecraft:fireball";
    }
};
