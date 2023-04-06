#pragma once

#include <spicygoat/util/Enum.h>

class SlabType : public Enum {
    explicit SlabType(const std::string& name) : Enum(name) {}

   public:
    static const SlabType top, bottom, _double;

    static const std::vector<SlabType> values;
};

inline const SlabType SlabType::top = SlabType("top");
inline const SlabType SlabType::bottom = SlabType("bottom");
inline const SlabType SlabType::_double = SlabType("double");

inline const std::vector<SlabType> SlabType::values = {top, bottom, _double};
