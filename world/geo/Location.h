//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_LOCATION_H
#define SPICYGOAT_LOCATION_H

#include <string>
#include "../chunks/Chunk.h"
#include "../chunks/ChunkColumn.h"

class Location {
public:
    Location();
    Location(double x, double y, double z, float yaw, float pitch);

    void setX(double x);

    void setY(double y);

    void setZ(double z);

    void setYaw(float yaw);

    void setPitch(float pitch);

    double getX() const;

    double getY() const;

    double getZ() const;

    float getYaw() const;

    float getPitch() const;

    int32_t getChunkX() const;

    int32_t getChunkZ() const;

    ChunkColumn * getChunkColumn() const;

    std::string toString() const;

    bool operator==(const Location &rhs) const;

    bool operator!=(const Location &rhs) const;

private:
    double x, y, z;
    float yaw, pitch;
};


#endif //SPICYGOAT_LOCATION_H
