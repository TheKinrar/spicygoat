//
// Created by thekinrar on 17/05/23.
//

#include <spicygoat/world/geo/Vector3d.h>

#include <cmath>

double Vector3d::length() const {
    return sqrt(lengthSquared());
}

double Vector3d::horizontalLength() const {
    return sqrt(horizontalLengthSquared());
}
