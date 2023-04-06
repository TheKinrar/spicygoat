//
// Created by thekinrar on 31/01/23.
//

#pragma once

class Vector3d {
    double x{}, y{}, z{};

   public:
    Vector3d() = default;
    Vector3d(double x, double y, double z) : x(x), y(y), z(z) {}

    [[nodiscard]]
    Vector3d add(double x, double y, double z) const {
        return {this->x + x, this->y + y, this->z + z};
    }

    [[nodiscard]]
    Vector3d add(Vector3d vec) const {
        return add(vec.getX(), vec.getY(), vec.getZ());
    }

    [[nodiscard]]
    Vector3d subtract(double x, double y, double z) const {
        return {this->x - x, this->y - y, this->z - z};
    }

    [[nodiscard]]
    Vector3d subtract(Vector3d vec) const {
        return subtract(vec.getX(), vec.getY(), vec.getZ());
    }

    [[nodiscard]]
    Vector3d multiply(double x, double y, double z) const {
        return {this->x * x, this->y * y, this->z * z};
    }

    [[nodiscard]]
    double getX() const {
        return x;
    }

    [[nodiscard]]
    double getY() const {
        return y;
    }

    [[nodiscard]]
    double getZ() const {
        return z;
    }

    void setX(double x) {
        Vector3d::x = x;
    }

    void setY(double y) {
        Vector3d::y = y;
    }

    void setZ(double z) {
        Vector3d::z = z;
    }

    [[nodiscard]]
    double lengthSquared() const {
        return x*x + y*y + z*z;
    }

    [[nodiscard]]
    double horizontalLengthSquared() const {
        return x*x + z*z;
    }

    [[nodiscard]]
    std::string toString() const {
        return std::string("Vector3d{") + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "}";
    }
};
