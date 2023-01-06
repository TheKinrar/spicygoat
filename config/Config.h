//
// Created by thekinrar on 25/12/22.
//

#ifndef SPICYGOAT_CONFIG_H
#define SPICYGOAT_CONFIG_H

#include <toml.hpp>

class Config {
   public:
    static const Config& get() {
        static Config instance;
        return instance;
    }

    int64_t gamemode;
    int64_t port;

   private:
    Config() : data(toml::parse<toml::preserve_comments>("config.toml")) {
        gamemode = toml::find<toml::integer>(data, "gamemode");
        port = toml::find<toml::integer>(data, "port");
    }

    toml::value data;
};

#endif  // SPICYGOAT_CONFIG_H
