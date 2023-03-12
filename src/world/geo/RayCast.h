//
// Created by thekinrar on 11/03/23.
//

#pragma once

#include "../World.h"

class RayCast {
    World& world;
    Position pos;
    Location loc;
    Vector3d vec;
    bool firstRound{};
    bool colX{}, colY{}, colZ{};

    bool slippery{};

   public:
    RayCast(World& world, Location loc, Vector3d vec) : world(world), loc(loc), vec(vec) {
        pos = {loc.getBlockX(), loc.getBlockY(), loc.getBlockZ()};
    }

    [[nodiscard]]
    bool isSlippery() const {
        return slippery;
    }

    void setSlippery(bool slippery) {
        RayCast::slippery = slippery;
    }

    [[nodiscard]]
    const Location& getLoc() const {
        return loc;
    }

    [[nodiscard]]
    const Vector3d& getVec() const {
        return vec;
    }

    [[nodiscard]]
    bool collidedX() const {
        return colX;
    }

    [[nodiscard]]
    bool collidedY() const {
        return colY;
    }

    [[nodiscard]]
    bool collidedZ() const {
        return colZ;
    }

    [[nodiscard]]
    bool collided() const {
        return colX || colY || colZ;
    }

    void cast();

   private:
    void advance(double time);
};
