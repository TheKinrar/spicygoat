//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <spicygoat/util/Enum.h>

class BedPart : public Enum {
    explicit BedPart(const std::string& name) : Enum(name) {}

   public:
    static const BedPart head, foot;

    static const std::vector<BedPart> values;
};

inline const BedPart BedPart::head = BedPart("head");
inline const BedPart BedPart::foot = BedPart("foot");

inline const std::vector<BedPart> BedPart::values = {head, foot};
