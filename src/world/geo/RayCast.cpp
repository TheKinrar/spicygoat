//
// Created by thekinrar on 11/03/23.
//

#include "RayCast.h"

#include "../../util/math.h"

static double nextBorder(double pos, double diff, bool firstRound) {
    if(firstRound && std::ceil(pos) == pos) return pos;
    else if(diff < 0) return std::ceil(pos - 1);
    else return std::floor(pos + 1);
}

void RayCast::cast() {
    firstRound = true;

    int sx = math::signOf(vec.getX());
    int sy = math::signOf(vec.getY());
    int sz = math::signOf(vec.getZ());

    while(vec.lengthSquared() != 0) {
        double tx = -1, ty = -1, tz = -1;
        double tMin = -1;

        if(vec.getX() != 0) {
            double dx = nextBorder(loc.getX(), vec.getX(), firstRound) - loc.getX();
            tx = dx / vec.getX();
            tMin = tx;
        }

        if(vec.getY() != 0) {
            double dy = nextBorder(loc.getY(), vec.getY(), firstRound) - loc.getY();
            ty = dy / vec.getY();
            if(tMin == -1 || ty < tMin) tMin = ty;
        }

        if(vec.getZ() != 0) {
            double dz = nextBorder(loc.getZ(), vec.getZ(), firstRound) - loc.getZ();
            tz = dz / vec.getZ();
            if(tMin == -1 || tz < tMin) tMin = tz;
        }

        firstRound = false;

        // We won't reach any border, advance the ray and exit
        if(tMin >= 1) {
            advance(1);
            break;
        } else if(tMin > 0) {
            advance(tMin);
        }

        int offX{}, offY{}, offZ{};

        if(tx == tMin) {
            if(world.getBlockState(pos.relative(sx, 0, 0))->getBlock().isAir()) {
                offX = sx;
            } else {
                colX = true;
            }
        }

        if(ty == tMin) {
            if(world.getBlockState(pos.relative(0, sy, 0))->getBlock().isAir()) {
                offY = sy;
            } else {
                colY = true;
            }
        }

        if(tz == tMin) {
            if(world.getBlockState(pos.relative(0, 0, sz))->getBlock().isAir()) {
                offZ = sz;
            } else {
                colZ = true;
            }
        }

        if(!collided()) {
            pos = pos.relative(offX, offY, offZ);

            if(!world.getBlockState(pos)->getBlock().isAir()) {
                colX = tx == tMin;
                colY = ty == tMin;
                colZ = tz == tMin;
            }
        }

        if(collided()) {
            if(slippery) {
                if(colX) vec.setX(0);
                if(colY) vec.setY(0);
                if(colZ) vec.setZ(0);
            } else {
                break;
            }
        }
    }
}

void RayCast::advance(double time) {
    auto inc = vec.multiply(time, time, time);
    loc = loc.add(inc);
    vec = vec.subtract(inc);
    firstRound = true;
}
