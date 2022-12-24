//
// Created by thekinrar on 02/04/19.
//

#include "Location.h"
#include "../World.h"

Location::Location() : Location(0, 0, 0, 0, 0) {}

Location::Location(double x, double y, double z, float yaw, float pitch) : x(x), y(y), z(z), yaw(yaw), pitch(pitch) {}

double Location::getX() const {
    return x;
}

double Location::getY() const {
    return y;
}

double Location::getZ() const {
    return z;
}

float Location::getYaw() const {
    return yaw;
}

float Location::getPitch() const {
    return pitch;
}

std::string Location::toString() const {
    return std::string("Location{") + std::to_string(x)
            + "," + std::to_string(y)
            + "," + std::to_string(z)
            + "," + std::to_string(yaw)
            + "," + std::to_string(pitch)
            + "}";
}

void Location::setX(double x) {
    Location::x = x;
}

void Location::setY(double y) {
    Location::y = y;
}

void Location::setZ(double z) {
    Location::z = z;
}

void Location::setYaw(float yaw) {
    Location::yaw = yaw;
}

void Location::setPitch(float pitch) {
    Location::pitch = pitch;
}

bool Location::operator==(const Location &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           z == rhs.z &&
           yaw == rhs.yaw &&
           pitch == rhs.pitch;
}

bool Location::operator!=(const Location &rhs) const {
    return !(rhs == *this);
}

int32_t Location::getChunkX() const {
    return (int32_t) (getX() / 16);
}

int32_t Location::getChunkZ() const {
    return (int32_t) (getZ() / 16);
}

double Location::distanceSquared(const Location &other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    double dz = z - other.z;

    return dx*dx + dy*dy + dz*dz;
}
