#pragma once

#include "../../util/Enum.h"

class BambooLeaves : public Enum {
    explicit BambooLeaves(const std::string& name) : Enum(name) {}

   public:
    static const BambooLeaves none, small, large;

    static const std::vector<BambooLeaves> values;
};

inline const BambooLeaves BambooLeaves::none = BambooLeaves("none");
inline const BambooLeaves BambooLeaves::small = BambooLeaves("small");
inline const BambooLeaves BambooLeaves::large = BambooLeaves("large");

inline const std::vector<BambooLeaves> BambooLeaves::values = {none, small, large};
