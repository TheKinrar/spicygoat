//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_LOCATION_H
#define SPICYGOAT_LOCATION_H

#include <string>

class Location {
public:
    Location(double x, double y, double z, float yaw, float pitch);

    double getX() const;

    double getY() const;

    double getZ() const;

    float getYaw() const;

    float getPitch() const;

    std::string toString() const;

private:
    double x, y, z;
    float yaw, pitch;
};


#endif //SPICYGOAT_LOCATION_H
