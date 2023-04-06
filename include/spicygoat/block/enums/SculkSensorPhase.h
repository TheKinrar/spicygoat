#pragma once

#include <spicygoat/util/Enum.h>

class SculkSensorPhase : public Enum {
    explicit SculkSensorPhase(const std::string& name) : Enum(name) {}

   public:
    static const SculkSensorPhase inactive, active, cooldown;

    static const std::vector<SculkSensorPhase> values;
};

inline const SculkSensorPhase SculkSensorPhase::inactive = SculkSensorPhase("inactive");
inline const SculkSensorPhase SculkSensorPhase::active = SculkSensorPhase("active");
inline const SculkSensorPhase SculkSensorPhase::cooldown = SculkSensorPhase("cooldown");

inline const std::vector<SculkSensorPhase> SculkSensorPhase::values = {inactive, active, cooldown};
