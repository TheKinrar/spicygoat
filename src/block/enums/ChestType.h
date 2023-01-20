#pragma once

#include "../../util/Enum.h"

class ChestType : public Enum {
    explicit ChestType(const std::string& name) : Enum(name) {}

   public:
    static const ChestType single, left, right;

    static const std::vector<ChestType> values;
};

inline const ChestType ChestType::single = ChestType("single");
inline const ChestType ChestType::left = ChestType("left");
inline const ChestType ChestType::right = ChestType("right");

inline const std::vector<ChestType> ChestType::values = {single, left, right};
