//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_LOCATION_H
#define SPICYGOAT_LOCATION_H

#include <cmath>
#include <string>

#include "../../util/math.h"
#include "Position.h"
#include "Vector3d.h"

class Location {
   public:
    Location();
    Location(double x, double y, double z, float yaw, float pitch);
    explicit Location(Position pos) : x(pos.getX()), y(pos.getY()), z(pos.getZ()), yaw(0), pitch(0) {};
    static Location center(Position pos) {
        return {pos.getX() + 0.5, pos.getY() + 0.5, pos.getZ() + 0.5, 0, 0};
    }

    void setX(double x);

    void setY(double y);

    void setZ(double z);

    void setYaw(float yaw);

    void setPitch(float pitch);

    [[nodiscard]]
    Location add(double x, double y, double z) const {
        return {this->x + x, this->y + y, this->z + z, yaw, pitch};
    }

    [[nodiscard]]
    Location add(Vector3d vec) const {
        return add(vec.getX(), vec.getY(), vec.getZ());
    }

    double getX() const;

    [[nodiscard]]
    int getBlockX() const {
        return std::floor(x);
    }

    double getY() const;

    [[nodiscard]]
    int getBlockY() const {
        return std::floor(y);
    }

    double getZ() const;

    [[nodiscard]]
    int getBlockZ() const {
        return std::floor(z);
    }

    float getYaw() const;

    float getPitch() const;

    [[nodiscard]]
    Position toPosition() const {
        return {static_cast<int32_t>(std::floor(x)), static_cast<int32_t>(std::floor(y)), static_cast<int32_t>(std::floor(z))};
    }

    [[nodiscard]]
    int32_t getChunkX() const {
        return static_cast<int32_t>(std::floor(x)) >> 4;
    }

    [[nodiscard]]
    int32_t getChunkY() const {
        return static_cast<int32_t>(std::floor(y)) >> 4;
    }

    [[nodiscard]]
    int32_t getChunkZ() const {
        return static_cast<int32_t>(std::floor(z)) >> 4;
    }

    [[nodiscard]] double distanceSquared(const Location &other) const;

    [[nodiscard]]
    Vector3d getDirection() const {
        double xRads = math::degToRad(getYaw());
        double yRads = math::degToRad(getPitch());

        double xz = std::cos(yRads);

        return {-xz * std::sin(xRads), -std::sin(yRads), xz * std::cos(xRads)};
    }

    std::string toString() const;

    bool operator==(const Location &rhs) const;

    bool operator!=(const Location &rhs) const;

   private:
    double x, y, z;
    float yaw, pitch;
};

#endif  // SPICYGOAT_LOCATION_H
