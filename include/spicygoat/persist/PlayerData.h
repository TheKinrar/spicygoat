//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include <filesystem>
#include <fstream>
#include <utility>

#include <io/izlibstream.h>
#include <io/ozlibstream.h>
#include <io/stream_reader.h>
#include <io/stream_writer.h>
#include <tag_compound.h>
#include <tag_list.h>
#include <tag_primitive.h>

class EntityPlayer;
class PlayerInventory;

#include <spicygoat/util/PlayerAbilities.h>
#include <spicygoat/util/GameMode.h>
#include <spicygoat/world/geo/Location.h>
#include <uuid.h>

class PlayerData {
    uuids::uuid id;
    std::unique_ptr<nbt::tag_compound> nbt;

   public:
    explicit PlayerData(const uuids::uuid& id) : id(id), nbt(std::make_unique<nbt::tag_compound>()) {}
    PlayerData(const uuids::uuid& id, std::unique_ptr<nbt::tag_compound> nbt) : id(id), nbt(std::move(nbt)) {}

    static std::unique_ptr<PlayerData> load(uuids::uuid id) {
        auto path = "world/playerdata/" + to_string(id) + ".dat";
        if(std::filesystem::exists(path)) {
            std::ifstream ifs(path);
            zlib::izlibstream buf(ifs);
            return std::make_unique<PlayerData>(id, nbt::io::read_compound(buf).second);
        } else {
            return std::make_unique<PlayerData>(id);
        }
    }

    void save() {
        std::ofstream ofs("world/playerdata/" + to_string(id) + ".dat");
        zlib::ozlibstream buf(ofs, Z_DEFAULT_COMPRESSION, true);
        nbt::io::write_tag("", *nbt, buf);
    }

    [[nodiscard]]
    Location getLocation(const Location& def) const {
        if(nbt->has_key("Pos")) {
            auto pos = nbt->at("Pos").as<nbt::tag_list>();
            auto rot = nbt->at("Rotation").as<nbt::tag_list>();
            return {
                pos[0].as<nbt::tag_double>(),
                pos[1].as<nbt::tag_double>(),
                pos[2].as<nbt::tag_double>(),
                rot[0].as<nbt::tag_float>(),
                rot[1].as<nbt::tag_float>()
            };
        } else {
            return def;
        }
    }

    void setLocation(const Location& loc) const {
        nbt::tag_list pos, rot;
        pos.push_back(loc.getX());
        pos.push_back(loc.getY());
        pos.push_back(loc.getZ());
        rot.push_back(loc.getYaw());
        rot.push_back(loc.getPitch());
        nbt->put("Pos", std::move(pos));
        nbt->put("Rotation", std::move(rot));
    }

    [[nodiscard]]
    PlayerInventory getInventory(EntityPlayer& player) const;

    void setInventory(const PlayerInventory& source);

    [[nodiscard]]
    PlayerAbilities getAbilities() const;

    void setAbilities(const PlayerAbilities& source);

    [[nodiscard]]
    GameMode::GameMode getGameMode(GameMode::GameMode def) const;

    void setGameMode(const GameMode::GameMode& source);

   private:
    static int dataSlotToNetwork(int slot) {
        if(slot == -106) // Off-hand
            return 45;
        if(slot == 100) // Boots
            return 8;
        if(slot == 101) // Leggings
            return 7;
        if(slot == 102) // Chestplate
            return 6;
        if(slot == 103) // Helmet
            return 5;

        if(slot >= 0) {
            if(slot <= 8)
                return slot + 36;
            if(slot <= 35)
                return slot;
        }

        throw std::runtime_error("Illegal data slot ID");
    }

    static int networkSlotToData(int slot) {
        if(slot == 45) // Off-hand
            return -106;
        if(slot == 8) // Boots
            return 100;
        if(slot == 7) // Leggings
            return 101;
        if(slot == 6) // Chestplate
            return 102;
        if(slot == 5) // Helmet
            return 103;

        if(slot <= 44) {
            if(slot >= 36)
                return slot - 36;
            if(slot >= 9)
                return slot;
        }

        throw std::runtime_error("Illegal network slot ID");
    }
};
