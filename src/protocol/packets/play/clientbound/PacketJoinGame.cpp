//
// Created by thekinrar on 01/04/19.
//

#include "PacketJoinGame.h"

#include <io/stream_writer.h>

#include <sstream>

#include "../../../../Server.h"
#include "../../../../config/Config.h"
#include "nbt_tags.h"
#include "resources_out/resources.h"

PacketJoinGame::PacketJoinGame(std::shared_ptr<EntityPlayer> player) {
    this->player = player;
}

std::vector<std::byte> nbtBytes(const nbt::tag_compound& tag) {
    std::ostringstream out;
    nbt::io::stream_writer(out).write_tag("", tag);
    std::string out_str = out.str();
    std::vector<std::byte> out_arr;
    for(char& c : out_str) {
        out_arr.push_back(static_cast<std::byte>(c));
    }
    return out_arr;
}

nbt::tag_compound overworldElement() {
    nbt::tag_compound overworld_e;
    overworld_e.put("infiniburn", nbt::tag_string("minecraft:infiniburn_overworld"));
    overworld_e.put("effects", nbt::tag_string("minecraft:overworld"));
    overworld_e.put("logical_height", nbt::tag_int(256));
    overworld_e.put("ambient_light", nbt::tag_float(0));
    overworld_e.put("piglin_safe", nbt::tag_byte(0));
    overworld_e.put("natural", nbt::tag_byte(1));
    overworld_e.put("respawn_anchor_works", nbt::tag_byte(0));
    overworld_e.put("has_skylight", nbt::tag_byte(1));
    overworld_e.put("bed_works", nbt::tag_byte(1));
    overworld_e.put("has_raids", nbt::tag_byte(1));
    overworld_e.put("ultrawarm", nbt::tag_byte(0));
    overworld_e.put("has_ceiling", nbt::tag_byte(0));
    overworld_e.put("coordinate_scale", nbt::tag_double(1));
    return overworld_e;
}

nbt::tag_compound overworld() {
    nbt::tag_compound overworld;
    overworld.put("name", nbt::tag_string("minecraft:overworld"));
    overworld.put("id", nbt::tag_int(0));
    overworld.put("element", std::move(overworldElement()));
    return overworld;
}

nbt::tag_compound dimRegistry() {
    nbt::tag_list dimensions(nbt::tag_type::Compound);
    dimensions.push_back(std::move(overworld()));

    nbt::tag_compound registry;
    registry.put("type", nbt::tag_string("minecraft:dimension_type"));
    registry.put("value", std::move(dimensions));
    return registry;
}

nbt::tag_compound oceanElement() {
    nbt::tag_compound sound;
    sound.put("tick_delay", nbt::tag_int(6000));
    sound.put("offset", nbt::tag_double(2));
    sound.put("sound", nbt::tag_string("minecraft:ambient.cave"));
    sound.put("block_search_extent", nbt::tag_int(8));

    nbt::tag_compound effects;
    effects.put("sky_color", nbt::tag_int(8103167));
    effects.put("water_fog_color", nbt::tag_int(329011));
    effects.put("fog_color", nbt::tag_int(12638463));
    effects.put("water_color", nbt::tag_int(4159204));
    effects.put("mood_sound", std::move(sound));

    nbt::tag_compound ocean_e;
    ocean_e.put("precipitation", nbt::tag_string("rain"));
    ocean_e.put("effects", std::move(effects));
    ocean_e.put("depth", nbt::tag_float(-1));
    ocean_e.put("temperature", nbt::tag_float(0.5));
    ocean_e.put("scale", nbt::tag_float(0.1));
    ocean_e.put("downfall", nbt::tag_float(0.5));
    ocean_e.put("category", nbt::tag_string("ocean"));
    return ocean_e;
}

nbt::tag_compound ocean() {
    nbt::tag_compound ocean;
    ocean.put("name", nbt::tag_string("minecraft:ocean"));
    ocean.put("id", nbt::tag_int(0));
    ocean.put("element", std::move(oceanElement()));
    return ocean;
}

nbt::tag_compound biomeRegistry() {
    nbt::tag_list biomes(nbt::tag_type::Compound);
    biomes.push_back(std::move(ocean()));

    nbt::tag_compound registry;
    registry.put("type", nbt::tag_string("minecraft:worldgen/biome"));
    registry.put("value", std::move(biomes));
    return registry;
}

std::vector<std::byte> PacketJoinGame::bytes() const {
    std::vector<std::byte> array;
    PacketData::writeVarInt(0x24, array);
    PacketData::writeInt(player->getEID(), array);
    PacketData::writeBoolean(false, array);  // TODO hardcore
    PacketData::writeUnsignedByte(static_cast<uint8_t>(player->getGamemode()), array);
    PacketData::writeUnsignedByte(255, array);  // TODO prev gamemode

    // TODO world names []
    PacketData::writeVarInt(1, array);
    PacketData::writeString("minecraft:overworld", array);

    /*nbt::tag_compound codec;
    codec.put("minecraft:dimension_type", std::move(dimRegistry()));
    codec.put("minecraft:worldgen/biome", std::move(biomeRegistry()));
    std::vector<std::byte> codecBytes = nbtBytes(codec);*/
    PacketData::writeByteArray(Resources::codec(), array);  // TODO dimensions/biomes codec

    PacketData::writeString("minecraft:overworld", array);  // current world type
    PacketData::writeString("minecraft:overworld", array);  // current world name

    PacketData::writeLong(0, array);         // TODO first 8B of sha-256 hash of seed
    PacketData::writeVarInt(1, array);       // TODO max players
    PacketData::writeVarInt(Config::get().viewDistance, array);
    PacketData::writeVarInt(10, array);      // TODO simulation distance
    PacketData::writeBoolean(false, array);  // TODO reduced debug info
    PacketData::writeBoolean(true, array);   // TODO enable respawn screen (false if doImmediateRespawn gamerule)
    PacketData::writeBoolean(false, array);  // TODO debug mode
    PacketData::writeBoolean(false, array);  // TODO superflat
    PacketData::writeBoolean(false, array);  // has death location
    return array;
}

std::string PacketJoinGame::toString() const {
    return std::string("PacketJoinGame{player=") + player->toString() + "}";
}
