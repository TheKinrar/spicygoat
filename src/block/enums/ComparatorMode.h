#pragma once

#include "../../util/Enum.h"

class ComparatorMode : public Enum {
    explicit ComparatorMode(const std::string& name) : Enum(name) {}

   public:
    static const ComparatorMode compare, subtract;

    static const std::vector<ComparatorMode> values;
};

inline const ComparatorMode ComparatorMode::compare = ComparatorMode("compare");
inline const ComparatorMode ComparatorMode::subtract = ComparatorMode("subtract");

inline const std::vector<ComparatorMode> ComparatorMode::values = {compare, subtract};
