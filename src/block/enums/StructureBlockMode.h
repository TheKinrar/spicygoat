#pragma once

#include "../../util/Enum.h"

class StructureBlockMode : public Enum {
    explicit StructureBlockMode(const std::string& name) : Enum(name) {}

   public:
    static const StructureBlockMode save, load, corner, data;

    static const std::vector<StructureBlockMode> values;
};

inline const StructureBlockMode StructureBlockMode::save = StructureBlockMode("save");
inline const StructureBlockMode StructureBlockMode::load = StructureBlockMode("load");
inline const StructureBlockMode StructureBlockMode::corner = StructureBlockMode("corner");
inline const StructureBlockMode StructureBlockMode::data = StructureBlockMode("data");

inline const std::vector<StructureBlockMode> StructureBlockMode::values = {save, load, corner, data};
