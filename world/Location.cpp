//
// Created by thekinrar on 02/04/19.
//

#include "Location.h"

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
