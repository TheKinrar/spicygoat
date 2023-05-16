#pragma once

#include <spicygoat/util/Enum.h>

class Instrument : public Enum {
    explicit Instrument(const std::string& name) : Enum(name) {}

   public:
    static const Instrument harp, basedrum, snare, hat, bass, flute, bell, guitar, chime, xylophone, iron_xylophone,
        cow_bell, didgeridoo, bit, banjo, pling, zombie, skeleton, creeper, dragon, wither_skeleton, piglin,
        custom_head;

    static const std::vector<Instrument> values;
};

inline const Instrument Instrument::harp = Instrument("harp");
inline const Instrument Instrument::basedrum = Instrument("basedrum");
inline const Instrument Instrument::snare = Instrument("snare");
inline const Instrument Instrument::hat = Instrument("hat");
inline const Instrument Instrument::bass = Instrument("bass");
inline const Instrument Instrument::flute = Instrument("flute");
inline const Instrument Instrument::bell = Instrument("bell");
inline const Instrument Instrument::guitar = Instrument("guitar");
inline const Instrument Instrument::chime = Instrument("chime");
inline const Instrument Instrument::xylophone = Instrument("xylophone");
inline const Instrument Instrument::iron_xylophone = Instrument("iron_xylophone");
inline const Instrument Instrument::cow_bell = Instrument("cow_bell");
inline const Instrument Instrument::didgeridoo = Instrument("didgeridoo");
inline const Instrument Instrument::bit = Instrument("bit");
inline const Instrument Instrument::banjo = Instrument("banjo");
inline const Instrument Instrument::pling = Instrument("pling");
inline const Instrument Instrument::zombie = Instrument("zombie");
inline const Instrument Instrument::skeleton = Instrument("skeleton");
inline const Instrument Instrument::creeper = Instrument("creeper");
inline const Instrument Instrument::dragon = Instrument("dragon");
inline const Instrument Instrument::wither_skeleton = Instrument("wither_skeleton");
inline const Instrument Instrument::piglin = Instrument("piglin");
inline const Instrument Instrument::custom_head = Instrument("custom_head");

inline const std::vector<Instrument> Instrument::values = {
    harp,      basedrum,       snare,           hat,        bass,       flute, bell,  guitar, chime,
    xylophone, iron_xylophone, cow_bell,        didgeridoo, bit,        banjo, pling, zombie, skeleton,
    creeper,   dragon,         wither_skeleton, piglin,     custom_head};
