#pragma once

#include "../../util/Enum.h"

class Tilt : public Enum {
    explicit Tilt(const std::string& name) : Enum(name) {}

   public:
    static const Tilt none, unstable, partial, full;

    static const std::vector<Tilt> values;
};

inline const Tilt Tilt::none = Tilt("none");
inline const Tilt Tilt::unstable = Tilt("unstable");
inline const Tilt Tilt::partial = Tilt("partial");
inline const Tilt Tilt::full = Tilt("full");

inline const std::vector<Tilt> Tilt::values = {none, unstable, partial, full};
