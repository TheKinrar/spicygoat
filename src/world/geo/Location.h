//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_LOCATION_H
#define SPICYGOAT_LOCATION_H

#include <string>

#include "Position.h"

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

    double getX() const;

    double getY() const;

    double getZ() const;

    float getYaw() const;

    float getPitch() const;

    int32_t getChunkX() const;

    int32_t getChunkZ() const;

    [[nodiscard]] double distanceSquared(const Location &other) const;

    std::string toString() const;

    bool operator==(const Location &rhs) const;

    bool operator!=(const Location &rhs) const;

   private:
    double x, y, z;
    float yaw, pitch;
};

#endif  // SPICYGOAT_LOCATION_H
