//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include <io/izlibstream.h>
#include <io/ozlibstream.h>
#include <io/stream_reader.h>
#include <io/stream_writer.h>
#include <tag_compound.h>
#include <tag_primitive.h>

#include <filesystem>
#include <fstream>
#include <utility>

#include "../world/geo/Location.h"
#include "uuid.h"

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
};
