#pragma once

#include "../../util/Enum.h"

class PistonType : public Enum {
    explicit PistonType(const std::string& name) : Enum(name) {}

   public:
    static const PistonType normal, sticky;

    static const std::vector<PistonType> values;
};

inline const PistonType PistonType::normal = PistonType("normal");
inline const PistonType PistonType::sticky = PistonType("sticky");

inline const std::vector<PistonType> PistonType::values = {normal, sticky};
