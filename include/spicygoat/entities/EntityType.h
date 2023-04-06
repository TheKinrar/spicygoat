//
// Created by thekinrar on 28/01/23.
//

#pragma once

#include <utility>

#include <spicygoat/util/Identifier.h>

class EntityType {
    const Identifier name;
    float width, height;

   public:
    EntityType(Identifier name, float width, float height) : name(std::move(name)), width(width), height(height) {}

    [[nodiscard]]
    const Identifier& getName() const {
        return name;
    }

    [[nodiscard]]
    float getWidth() const {
        return width;
    }

    [[nodiscard]]
    float getHeight() const {
        return height;
    }
};
