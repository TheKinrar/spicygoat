//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include "../../util/Enum.h"

class Attachment : public Enum {
    explicit Attachment(const std::string& name) : Enum(name) {}

   public:
    static const Attachment floor, ceiling, single_wall, double_wall;

    static const std::vector<Attachment> values;
};

inline const Attachment Attachment::floor = Attachment("floor");
inline const Attachment Attachment::ceiling = Attachment("ceiling");
inline const Attachment Attachment::single_wall = Attachment("single_wall");
inline const Attachment Attachment::double_wall = Attachment("double_wall");

inline const std::vector<Attachment> Attachment::values = {floor, ceiling, single_wall, double_wall};
