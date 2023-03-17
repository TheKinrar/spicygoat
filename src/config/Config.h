//
// Created by thekinrar on 25/12/22.
//

#ifndef SPICYGOAT_CONFIG_H
#define SPICYGOAT_CONFIG_H

#include <toml.hpp>

#include "../util/GameMode.h"

class Config {
   public:
    static const Config& get() {
        static Config instance;
        return instance;
    }

    GameMode::GameMode gamemode;
    int64_t port;
    int viewDistance;
    int entityViewDistance;

   private:
    Config() : data(toml::parse<toml::preserve_comments>("config.toml")) {
        gamemode = GameMode::parse(toml::find_or<toml::integer>(data, "gamemode", 0));
        port = toml::find_or<toml::integer>(data, "port", 25565);
        viewDistance = (int) toml::find_or<toml::integer>(data, "view_distance", 10);
        entityViewDistance = (int) toml::find_or<toml::integer>(data, "entity_view_distance", 50);
    }

    toml::value data;
};

#endif  // SPICYGOAT_CONFIG_H
