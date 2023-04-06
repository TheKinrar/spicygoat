//
// Created by thekinrar on 10/03/23.
//

#pragma once

#include <algorithm>

namespace math {

inline double clamp(double v, double min, double max) {
    return std::max(std::min(v, max), min);
}

inline int signOf(double v) {
    return v < 0 ? -1 : 1;
}

inline int negativeSignOf(double v) {
    return v < 0 ? -1 : 0;
}

inline double degToRad(float deg) {
    return deg * (std::numbers::pi / 180);
}

}
